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
 int /*<<< orphan*/  Q3IMAGE_BYTESPERPIXEL ; 
 int /*<<< orphan*/  UnfilterImage (int*,int,int,int) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static qboolean DecodeImageNonInterlaced(struct PNG_Chunk_IHDR *IHDR,
		byte                  *OutBuffer, 
		uint8_t               *DecompressedData,
		uint32_t               DecompressedDataLength,
		qboolean               HasTransparentColour,
		uint8_t               *TransparentColour,
		uint8_t               *OutPal)
{
	uint32_t IHDR_Width;
	uint32_t IHDR_Height;
	uint32_t BytesPerScanline, BytesPerPixel, PixelsPerByte;
	uint32_t  w, h, p;
	byte *OutPtr;
	uint8_t *DecompPtr;

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
	 *  Calculate the size of one scanline
	 */

	BytesPerScanline = (IHDR_Width * BytesPerPixel + (PixelsPerByte - 1)) / PixelsPerByte;

	/*
	 *  Check if we have enough data for the whole image.
	 */

	if(!(DecompressedDataLength == ((BytesPerScanline + 1) * IHDR_Height)))
	{
		return(qfalse);
	}

	/*
	 *  Unfilter the image.
	 */

	if(!UnfilterImage(DecompressedData, IHDR_Height, BytesPerScanline, BytesPerPixel))
	{
		return(qfalse);
	}

	/*
	 *  Set the working pointers to the beginning of the buffers.
	 */

	OutPtr = OutBuffer;
	DecompPtr = DecompressedData;

	/*
	 *  Create the output image.
	 */

	for(h = 0; h < IHDR_Height; h++)
	{
		/*
		 *  Count the pixels on the scanline for those multipixel bytes
		 */

		uint32_t CurrPixel;

		/*
		 *  skip FilterType
		 */

		DecompPtr++;

		/*
		 *  Reset the pixel count.
		 */

		CurrPixel = 0;

		for(w = 0; w < (BytesPerScanline / BytesPerPixel); w++)
		{
			if(PixelsPerByte > 1)
			{
				uint8_t  Mask;
				uint32_t Shift;
				uint8_t  SinglePixel;

				for(p = 0; p < PixelsPerByte; p++)
				{
					if(CurrPixel < IHDR_Width)
					{
						Mask  = (1 << IHDR->BitDepth) - 1;
						Shift = (PixelsPerByte - 1 - p) * IHDR->BitDepth;

						SinglePixel = ((DecompPtr[0] & (Mask << Shift)) >> Shift);

						if(!ConvertPixel(IHDR, OutPtr, &SinglePixel, HasTransparentColour, TransparentColour, OutPal))
						{
							return(qfalse);
						}

						OutPtr += Q3IMAGE_BYTESPERPIXEL;
						CurrPixel++;
					}
				}

			}
			else
			{
				if(!ConvertPixel(IHDR, OutPtr, DecompPtr, HasTransparentColour, TransparentColour, OutPal))
				{
					return(qfalse);
				}


				OutPtr += Q3IMAGE_BYTESPERPIXEL;
			}

			DecompPtr += BytesPerPixel;
		}
	}

	return(qtrue);
}