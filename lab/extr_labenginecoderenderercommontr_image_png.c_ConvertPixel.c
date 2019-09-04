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
struct PNG_Chunk_IHDR {int ColourType; int BitDepth; } ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int byte ;

/* Variables and functions */
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
 int Q3IMAGE_BYTESPERPIXEL ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static qboolean ConvertPixel(struct PNG_Chunk_IHDR *IHDR,
		byte                  *OutPtr,
		uint8_t               *DecompPtr,
		qboolean               HasTransparentColour,
		uint8_t               *TransparentColour,
		uint8_t               *OutPal)
{
	/*
	 *  input verification
	 */

	if(!(IHDR && OutPtr && DecompPtr && TransparentColour && OutPal))
	{
		return(qfalse);
	}

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
					uint8_t Step;
					uint8_t GreyValue;

					Step = 0xFF / ((1 << IHDR->BitDepth) - 1);

					GreyValue = DecompPtr[0] * Step;

					OutPtr[0] = GreyValue;
					OutPtr[1] = GreyValue;
					OutPtr[2] = GreyValue;
					OutPtr[3] = 0xFF;

					/*
					 *  Grey supports full transparency for one specified colour
					 */

					if(HasTransparentColour)
					{
						if(TransparentColour[1] == DecompPtr[0])
						{
							OutPtr[3] = 0x00;
						}
					}


					break;
				}

				case PNG_BitDepth_8 :
				case PNG_BitDepth_16 :
				{
					OutPtr[0] = DecompPtr[0];
					OutPtr[1] = DecompPtr[0];
					OutPtr[2] = DecompPtr[0];
					OutPtr[3] = 0xFF;

					/*
					 *  Grey supports full transparency for one specified colour
					 */

					if(HasTransparentColour)
					{
						if(IHDR->BitDepth == PNG_BitDepth_8)
						{
							if(TransparentColour[1] == DecompPtr[0])
							{
								OutPtr[3] = 0x00;
							}
						}
						else
						{
							if((TransparentColour[0] == DecompPtr[0]) && (TransparentColour[1] == DecompPtr[1]))
							{
								OutPtr[3] = 0x00;
							}
						}
					}

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
				case PNG_BitDepth_8 :
				{
					OutPtr[0] = DecompPtr[0];
					OutPtr[1] = DecompPtr[1];
					OutPtr[2] = DecompPtr[2];
					OutPtr[3] = 0xFF;

					/*
					 *  True supports full transparency for one specified colour
					 */

					if(HasTransparentColour)
					{
						if((TransparentColour[1] == DecompPtr[0]) &&
								(TransparentColour[3] == DecompPtr[1]) &&
								(TransparentColour[5] == DecompPtr[2]))
						{
							OutPtr[3] = 0x00;
						}
					}

					break;
				}

				case PNG_BitDepth_16 :
				{
					/*
					 *  We use only the upper byte.
					 */

					OutPtr[0] = DecompPtr[0];
					OutPtr[1] = DecompPtr[2];
					OutPtr[2] = DecompPtr[4];
					OutPtr[3] = 0xFF;

					/*
					 *  True supports full transparency for one specified colour
					 */

					if(HasTransparentColour)
					{
						if((TransparentColour[0] == DecompPtr[0]) && (TransparentColour[1] == DecompPtr[1]) &&
								(TransparentColour[2] == DecompPtr[2]) && (TransparentColour[3] == DecompPtr[3]) &&
								(TransparentColour[4] == DecompPtr[4]) && (TransparentColour[5] == DecompPtr[5]))
						{
							OutPtr[3] = 0x00;
						}
					}

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
			OutPtr[0] = OutPal[DecompPtr[0] * Q3IMAGE_BYTESPERPIXEL + 0];
			OutPtr[1] = OutPal[DecompPtr[0] * Q3IMAGE_BYTESPERPIXEL + 1];
			OutPtr[2] = OutPal[DecompPtr[0] * Q3IMAGE_BYTESPERPIXEL + 2];
			OutPtr[3] = OutPal[DecompPtr[0] * Q3IMAGE_BYTESPERPIXEL + 3];

			break;
		}

		case PNG_ColourType_GreyAlpha :
		{
			switch(IHDR->BitDepth)
			{
				case PNG_BitDepth_8 :
				{
					OutPtr[0] = DecompPtr[0];
					OutPtr[1] = DecompPtr[0];
					OutPtr[2] = DecompPtr[0];
					OutPtr[3] = DecompPtr[1];

					break;
				}

				case PNG_BitDepth_16 :
				{
					/*
					 *  We use only the upper byte.
					 */

					OutPtr[0] = DecompPtr[0];
					OutPtr[1] = DecompPtr[0];
					OutPtr[2] = DecompPtr[0];
					OutPtr[3] = DecompPtr[2];

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
				{
					OutPtr[0] = DecompPtr[0];
					OutPtr[1] = DecompPtr[1];
					OutPtr[2] = DecompPtr[2];
					OutPtr[3] = DecompPtr[3];

					break;
				}

				case PNG_BitDepth_16 :
				{
					/*
					 *  We use only the upper byte.
					 */

					OutPtr[0] = DecompPtr[0];
					OutPtr[1] = DecompPtr[2];
					OutPtr[2] = DecompPtr[4];
					OutPtr[3] = DecompPtr[6];

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

	return(qtrue);
}