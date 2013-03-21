 /*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __itkOrientedBoundingBoxImageLabelMapFilter_h
#define __itkOrientedBoundingBoxImageLabelMapFilter_h

#include "itkInPlaceLabelMapFilter.h"
#include "itkOrientedBoundingBoxLabelMapFilter.h"
#include "itkInterpolateImageFunction.h"

namespace itk
{

/** \class OrientedBoundingBoxImageLabelMapFilter
 * \ingroup ITKLabelMap
 */

template< class TImage,
          class TFeatureImage = typename TImage::LabelObjectType::AttributeImageType,
          class TSuperclass =  OrientedBoundingBoxLabelMapFilter<TImage> >
class ITK_EXPORT OrientedBoundingBoxImageLabelMapFilter:
  public TSuperclass
{
public:
  /** Standard class typedefs. */
  typedef OrientedBoundingBoxImageLabelMapFilter Self;
  typedef TSuperclass                       Superclass;
  typedef SmartPointer< Self >              Pointer;
  typedef SmartPointer< const Self >        ConstPointer;

  /** Some convenient typedefs. */
  typedef TImage                               ImageType;
  typedef typename ImageType::Pointer          ImagePointer;
  typedef typename ImageType::ConstPointer     ImageConstPointer;
  typedef typename ImageType::PixelType        PixelType;
  typedef typename ImageType::IndexType        IndexType;
  typedef typename ImageType::SizeType         SizeType;
  typedef typename ImageType::LabelObjectType  LabelObjectType;

  typedef typename ImageType::SpacingType       SpacingType;

  typedef TFeatureImage FeatureImageType;
  typedef typename LabelObjectType::AttributeImageType AttributeImageType;
  typedef typename AttributeImageType::PixelType AttributeImagePixelType;

  /** Interpolator typedef. */
  typedef InterpolateImageFunction< FeatureImageType, double >     InterpolatorType;

  /** ImageDimension constants */
  itkStaticConstMacro(ImageDimension, unsigned int, TImage::ImageDimension);

  /** Standard New method. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(OrientedBoundingBoxImageLabelMapFilter, TSuperclass);

  itkSetInputMacro(FeatureImage, FeatureImageType)
  itkGetInputMacro(FeatureImage, FeatureImageType)

  /** Specifies an additional amount to grow or shrink the bounding
   * box by when extracting to the output image, physical
   * size. Positive numbers expand the image, while negative shrink.
   *
   * Defaults to -0.5, corresponding to one half-pixel with the
   * default spacing. This is an adjustment for center-pixel physical
   * locations, so that the edge of the pixel's extent corresponds to
   * the edge of the oriented bounding box.
   */
  itkSetMacro(PaddingOffset, SpacingType);
  itkGetConstMacro(PaddingOffset, SpacingType);
  void SetPaddingOffset( typename SpacingType::ValueType o );

  /** Get/Set the interpolator function use to resample the feature
   * image. The default is LinearInterpolateImageFunction.
  */
  itkSetObjectMacro(Interpolator, InterpolatorType);
  itkGetModifiableObjectMacro(Interpolator, InterpolatorType);

  /** Get/Set the pixel value when a transformed pixel is outside of the
   * image.  The default default pixel value is 0. */
  itkSetMacro(DefaultPixelValue, AttributeImagePixelType);
  itkGetConstReferenceMacro(DefaultPixelValue, AttributeImagePixelType);


  /** Specifies that spacing used to resample the attribute image
   * onto.
   *
   * Defaults to 1.0;
   **/
  itkSetMacro(AttributeImageSpacing, SpacingType);
  itkGetConstMacro(AttributeImageSpacing, SpacingType);

protected:
    OrientedBoundingBoxImageLabelMapFilter();

  virtual void ThreadedProcessLabelObject(LabelObjectType *labelObject);

  void PrintSelf(std::ostream & os, Indent indent) const;

private:
  OrientedBoundingBoxImageLabelMapFilter(const Self &); //purposely not implemented
  void operator=(const Self &);      //purposely not implemented

  SpacingType m_PaddingOffset;
  SpacingType m_AttributeImageSpacing;

  typename InterpolatorType::Pointer m_Interpolator;
  AttributeImagePixelType            m_DefaultPixelValue;
};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkOrientedBoundingBoxImageLabelMapFilter.hxx"
#endif

#endif // __itkOrientedBoundingBoxImageLabelMapFilter_h