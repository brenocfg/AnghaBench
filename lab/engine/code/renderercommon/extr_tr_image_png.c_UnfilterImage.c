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
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
#define  PNG_FilterType_Average 132 
#define  PNG_FilterType_None 131 
#define  PNG_FilterType_Paeth 130 
#define  PNG_FilterType_Sub 129 
#define  PNG_FilterType_Up 128 
 int PredictPaeth (int,int,int) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static qboolean UnfilterImage(uint8_t  *DecompressedData, 
		uint32_t  ImageHeight,
		uint32_t  BytesPerScanline, 
		uint32_t  BytesPerPixel)
{
	uint8_t   *DecompPtr;
	uint8_t   FilterType;
	uint8_t  *PixelLeft, *PixelUp, *PixelUpLeft;
	uint32_t  w, h, p;

	/*
	 *  some zeros for the filters
	 */

	uint8_t Zeros[8] = {0, 0, 0, 0, 0, 0, 0, 0};

	/*
	 *  input verification
	 */

	if(!(DecompressedData && BytesPerPixel))
	{
		return(qfalse);
	}

	/*
	 *  ImageHeight and BytesPerScanline can be zero in small interlaced images.
	 */

	if((!ImageHeight) || (!BytesPerScanline))
	{
		return(qtrue);
	}

	/*
	 *  Set the pointer to the start of the decompressed Data.
	 */

	DecompPtr = DecompressedData;

	/*
	 *  Un-filtering is done in place.
	 */

	/*
	 *  Go trough all scanlines.
	 */

	for(h = 0; h < ImageHeight; h++)
	{
		/*
		 *  Every scanline starts with a FilterType byte.
		 */

		FilterType = *DecompPtr;
		DecompPtr++;

		/*
		 *  Left pixel of the first byte in a scanline is zero.
		 */

		PixelLeft = Zeros;

		/*
		 *  Set PixelUp to previous line only if we are on the second line or above.
		 *
		 *  Plus one byte for the FilterType
		 */

		if(h > 0)
		{
			PixelUp = DecompPtr - (BytesPerScanline + 1);
		}
		else
		{
			PixelUp = Zeros;
		}

		/*
		 * The pixel left to the first pixel of the previous scanline is zero too.
		 */

		PixelUpLeft = Zeros;

		/*
		 *  Cycle trough all pixels of the scanline.
		 */

		for(w = 0; w < (BytesPerScanline / BytesPerPixel); w++)
		{
			/*
			 *  Cycle trough the bytes of the pixel.
			 */

			for(p = 0; p < BytesPerPixel; p++)
			{
				switch(FilterType)
				{ 
					case PNG_FilterType_None :
					{
						/*
						 *  The byte is unfiltered.
						 */

						break;
					}

					case PNG_FilterType_Sub :
					{
						DecompPtr[p] += PixelLeft[p];

						break;
					}

					case PNG_FilterType_Up :
					{
						DecompPtr[p] += PixelUp[p];

						break;
					}

					case PNG_FilterType_Average :
					{
						DecompPtr[p] += ((uint8_t) ((((uint16_t) PixelLeft[p]) + ((uint16_t) PixelUp[p])) / 2));

						break;
					}

					case PNG_FilterType_Paeth :
					{
						DecompPtr[p] += PredictPaeth(PixelLeft[p], PixelUp[p], PixelUpLeft[p]);

						break;
					}

					default :
					{
						return(qfalse);
					}
				}
			}

			PixelLeft = DecompPtr;

			/*
			 *  We only have an upleft pixel if we are on the second line or above.
			 */

			if(h > 0)
			{
				PixelUpLeft = DecompPtr - (BytesPerScanline + 1);
			}

			/*
			 *  Skip to the next pixel.
			 */

			DecompPtr += BytesPerPixel;

			/*
			 *  We only have a previous line if we are on the second line and above.
			 */

			if(h > 0)
			{
				PixelUp = DecompPtr - (BytesPerScanline + 1);
			}
		}
	}

	return(qtrue);
}