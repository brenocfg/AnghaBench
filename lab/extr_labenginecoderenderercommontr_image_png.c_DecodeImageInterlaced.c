#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct PNG_Chunk_IHDR {int ColourType; int BitDepth; int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; } ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int BigLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConvertPixel (struct PNG_Chunk_IHDR*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int*,int*) ; 
 int PNG_Adam7_NumPasses ; 
#define  PNG_BitDepth_1 137 
#define  PNG_BitDepth_16 136 
#define  PNG_BitDepth_2 135 
#define  PNG_BitDepth_4 134 
#define  PNG_BitDepth_8 133 
#define  PNG_ColourType_Grey 132 
#define  PNG_ColourType_GreyAlpha 131 
#define  PNG_ColourType_Indexed 130 
#define  PNG_ColourType_True 129 
#define  PNG_ColourType_TrueAlpha 128 
 int PNG_NumColourComponents_Grey ; 
 int PNG_NumColourComponents_GreyAlpha ; 
 int PNG_NumColourComponents_Indexed ; 
 int PNG_NumColourComponents_True ; 
 int PNG_NumColourComponents_TrueAlpha ; 
 int Q3IMAGE_BYTESPERPIXEL ; 
 int /*<<< orphan*/  UnfilterImage (int*,int,int,int) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static qboolean DecodeImageInterlaced(struct PNG_Chunk_IHDR *IHDR,
		byte                  *OutBuffer, 
		uint8_t               *DecompressedData,
		uint32_t               DecompressedDataLength,
		qboolean               HasTransparentColour,
		uint8_t               *TransparentColour,
		uint8_t               *OutPal)
{
	uint32_t IHDR_Width;
	uint32_t IHDR_Height;
	uint32_t BytesPerScanline[PNG_Adam7_NumPasses], BytesPerPixel, PixelsPerByte;
	uint32_t PassWidth[PNG_Adam7_NumPasses], PassHeight[PNG_Adam7_NumPasses];
	uint32_t WSkip[PNG_Adam7_NumPasses], WOffset[PNG_Adam7_NumPasses], HSkip[PNG_Adam7_NumPasses], HOffset[PNG_Adam7_NumPasses];
	uint32_t w, h, p, a;
	byte *OutPtr;
	uint8_t *DecompPtr;
	uint32_t TargetLength;

	/*
	 *  input verification
	 */

	if(!(IHDR && OutBuffer && DecompressedData && DecompressedDataLength && TransparentColour && OutPal))
	{
		return(qfalse);
	}

	/*
	 *  byte swapping
	 */

	IHDR_Width  = BigLong(IHDR->Width);
	IHDR_Height = BigLong(IHDR->Height);

	/*
	 *  Skip and Offset for the passes.
	 */

	WSkip[0]   = 8;
	WOffset[0] = 0;
	HSkip[0]   = 8;
	HOffset[0] = 0;

	WSkip[1]   = 8;
	WOffset[1] = 4;
	HSkip[1]   = 8;
	HOffset[1] = 0;

	WSkip[2]   = 4;
	WOffset[2] = 0;
	HSkip[2]   = 8;
	HOffset[2] = 4;

	WSkip[3]   = 4;
	WOffset[3] = 2;
	HSkip[3]   = 4;
	HOffset[3] = 0;

	WSkip[4]   = 2;
	WOffset[4] = 0;
	HSkip[4]   = 4;
	HOffset[4] = 2;

	WSkip[5]   = 2;
	WOffset[5] = 1;
	HSkip[5]   = 2;
	HOffset[5] = 0;

	WSkip[6]   = 1;
	WOffset[6] = 0;
	HSkip[6]   = 2;
	HOffset[6] = 1;

	/*
	 *  Calculate the sizes of the passes.
	 */

	PassWidth[0]  = (IHDR_Width  + 7) / 8;
	PassHeight[0] = (IHDR_Height + 7) / 8;

	PassWidth[1]  = (IHDR_Width  + 3) / 8;
	PassHeight[1] = (IHDR_Height + 7) / 8;

	PassWidth[2]  = (IHDR_Width  + 3) / 4;
	PassHeight[2] = (IHDR_Height + 3) / 8;

	PassWidth[3]  = (IHDR_Width  + 1) / 4;
	PassHeight[3] = (IHDR_Height + 3) / 4;

	PassWidth[4]  = (IHDR_Width  + 1) / 2;
	PassHeight[4] = (IHDR_Height + 1) / 4;

	PassWidth[5]  = (IHDR_Width  + 0) / 2;
	PassHeight[5] = (IHDR_Height + 1) / 2;

	PassWidth[6]  = (IHDR_Width  + 0) / 1;
	PassHeight[6] = (IHDR_Height + 0) / 2;

	/*
	 *  information for un-filtering
	 */

	switch(IHDR->ColourType)
	{
		case PNG_ColourType_Grey :
		{
			switch(IHDR->BitDepth)
			{
				case PNG_BitDepth_1 :
				case PNG_BitDepth_2 :
				case PNG_BitDepth_4 :
				{
					BytesPerPixel    = 1;
					PixelsPerByte    = 8 / IHDR->BitDepth;

					break;
				}

				case PNG_BitDepth_8  :
				case PNG_BitDepth_16 :
				{
					BytesPerPixel    = (IHDR->BitDepth / 8) * PNG_NumColourComponents_Grey;
					PixelsPerByte    = 1;

					break;
				}

				default :
				{
					return(qfalse);
				}
			}

			break;
		}

		case PNG_ColourType_True :
		{
			switch(IHDR->BitDepth)
			{
				case PNG_BitDepth_8  :
				case PNG_BitDepth_16 :
				{
					BytesPerPixel    = (IHDR->BitDepth / 8) * PNG_NumColourComponents_True;
					PixelsPerByte    = 1;

					break;
				}

				default :
				{
					return(qfalse);
				}
			}

			break;
		}

		case PNG_ColourType_Indexed :
		{
			switch(IHDR->BitDepth)
			{
				case PNG_BitDepth_1 :
				case PNG_BitDepth_2 :
				case PNG_BitDepth_4 :
				{
					BytesPerPixel    = 1;
					PixelsPerByte    = 8 / IHDR->BitDepth;

					break;
				}

				case PNG_BitDepth_8 :
				{
					BytesPerPixel    = PNG_NumColourComponents_Indexed;
					PixelsPerByte    = 1;

					break;
				}

				default :
				{
					return(qfalse);
				}
			}

			break;
		}

		case PNG_ColourType_GreyAlpha :
		{
			switch(IHDR->BitDepth)
			{
				case PNG_BitDepth_8 :
				case PNG_BitDepth_16 :
				{
					BytesPerPixel    = (IHDR->BitDepth / 8) * PNG_NumColourComponents_GreyAlpha;
					PixelsPerByte    = 1;

					break;
				}

				default :
				{
					return(qfalse);
				}
			}

			break;
		}

		case PNG_ColourType_TrueAlpha :
		{
			switch(IHDR->BitDepth)
			{
				case PNG_BitDepth_8 :
				case PNG_BitDepth_16 :
				{
					BytesPerPixel    = (IHDR->BitDepth / 8) * PNG_NumColourComponents_TrueAlpha;
					PixelsPerByte    = 1;

					break;
				}

				default :
				{
					return(qfalse);
				}
			}

			break;
		}

		default :
		{
			return(qfalse);
		}
	}

	/*
	 *  Calculate the size of the scanlines per pass
	 */

	for(a = 0; a < PNG_Adam7_NumPasses; a++)
	{
		BytesPerScanline[a] = (PassWidth[a] * BytesPerPixel + (PixelsPerByte - 1)) / PixelsPerByte;
	}

	/*
	 *  Calculate the size of all passes
	 */

	TargetLength = 0;

	for(a = 0; a < PNG_Adam7_NumPasses; a++)
	{
		TargetLength += ((BytesPerScanline[a] + (BytesPerScanline[a] ? 1 : 0)) * PassHeight[a]);
	}

	/*
	 *  Check if we have enough data for the whole image.
	 */

	if(!(DecompressedDataLength == TargetLength))
	{
		return(qfalse);
	}

	/*
	 *  Unfilter the image.
	 */

	DecompPtr = DecompressedData;

	for(a = 0; a < PNG_Adam7_NumPasses; a++)
	{
		if(!UnfilterImage(DecompPtr, PassHeight[a], BytesPerScanline[a], BytesPerPixel))
		{
			return(qfalse);
		}

		DecompPtr += ((BytesPerScanline[a] + (BytesPerScanline[a] ? 1 : 0)) * PassHeight[a]);
	}

	/*
	 *  Set the working pointers to the beginning of the buffers.
	 */

	DecompPtr = DecompressedData;

	/*
	 *  Create the output image.
	 */

	for(a = 0; a < PNG_Adam7_NumPasses; a++)
	{
		for(h = 0; h < PassHeight[a]; h++)
		{
			/*
			 *  Count the pixels on the scanline for those multipixel bytes
			 */

			uint32_t CurrPixel;

			/*
			 *  skip FilterType
			 *  but only when the pass has a width bigger than zero
			 */

			if(BytesPerScanline[a])
			{
				DecompPtr++;
			}

			/*
			 *  Reset the pixel count.
			 */

			CurrPixel = 0;

			for(w = 0; w < (BytesPerScanline[a] / BytesPerPixel); w++)
			{
				if(PixelsPerByte > 1)
				{
					uint8_t  Mask;
					uint32_t Shift;
					uint8_t  SinglePixel;

					for(p = 0; p < PixelsPerByte; p++)
					{
						if(CurrPixel < PassWidth[a])
						{
							Mask  = (1 << IHDR->BitDepth) - 1;
							Shift = (PixelsPerByte - 1 - p) * IHDR->BitDepth;

							SinglePixel = ((DecompPtr[0] & (Mask << Shift)) >> Shift);

							OutPtr = OutBuffer + (((((h * HSkip[a]) + HOffset[a]) * IHDR_Width) + ((CurrPixel * WSkip[a]) + WOffset[a])) * Q3IMAGE_BYTESPERPIXEL);

							if(!ConvertPixel(IHDR, OutPtr, &SinglePixel, HasTransparentColour, TransparentColour, OutPal))
							{
								return(qfalse);
							}

							CurrPixel++;
						}
					}

				}
				else
				{
					OutPtr = OutBuffer + (((((h * HSkip[a]) + HOffset[a]) * IHDR_Width) + ((w * WSkip[a]) + WOffset[a])) * Q3IMAGE_BYTESPERPIXEL);

					if(!ConvertPixel(IHDR, OutPtr, DecompPtr, HasTransparentColour, TransparentColour, OutPal))
					{
						return(qfalse);
					}
				}

				DecompPtr += BytesPerPixel;
			}
		}
	}

	return(qtrue);
}