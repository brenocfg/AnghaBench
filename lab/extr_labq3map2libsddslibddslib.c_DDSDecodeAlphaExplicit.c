#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned short a; scalar_t__ b; scalar_t__ g; scalar_t__ r; } ;
typedef  TYPE_1__ ddsColor_t ;
struct TYPE_5__ {int /*<<< orphan*/ * row; } ;
typedef  TYPE_2__ ddsAlphaBlockExplicit_t ;

/* Variables and functions */
 unsigned short DDSLittleShort (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DDSDecodeAlphaExplicit( unsigned int *pixel, ddsAlphaBlockExplicit_t *alphaBlock, int width, unsigned int alphaZero ){
	int row, pix;
	unsigned short word;
	ddsColor_t color;


	/* clear color */
	color.r = 0;
	color.g = 0;
	color.b = 0;

	/* walk rows */
	for ( row = 0; row < 4; row++, pixel += ( width - 4 ) )
	{
		word = DDSLittleShort( alphaBlock->row[ row ] );

		/* walk pixels */
		for ( pix = 0; pix < 4; pix++ )
		{
			/* zero the alpha bits of image pixel */
			*pixel &= alphaZero;
			color.a = word & 0x000F;
			color.a = color.a | ( color.a << 4 );
			*pixel |= *( (unsigned int*) &color );
			word >>= 4;     /* move next bits to lowest 4 */
			pixel++;        /* move to next pixel in the row */

		}
	}
}