#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int* row; } ;
typedef  TYPE_1__ ddsColorBlock_t ;

/* Variables and functions */

__attribute__((used)) static void DDSDecodeColorBlock( unsigned int *pixel, ddsColorBlock_t *block, int width, unsigned int colors[ 4 ] ){
	int r, n;
	unsigned int bits;
	unsigned int masks[] = { 3, 12, 3 << 4, 3 << 6 };       /* bit masks = 00000011, 00001100, 00110000, 11000000 */
	int shift[] = { 0, 2, 4, 6 };


	/* r steps through lines in y */
	for ( r = 0; r < 4; r++, pixel += ( width - 4 ) )  /* no width * 4 as unsigned int ptr inc will * 4 */
	{
		/* width * 4 bytes per pixel per line, each j dxtc row is 4 lines of pixels */

		/* n steps through pixels */
		for ( n = 0; n < 4; n++ )
		{
			bits = block->row[ r ] & masks[ n ];
			bits >>= shift[ n ];

			switch ( bits )
			{
			case 0:
				*pixel = colors[ 0 ];
				pixel++;
				break;

			case 1:
				*pixel = colors[ 1 ];
				pixel++;
				break;

			case 2:
				*pixel = colors[ 2 ];
				pixel++;
				break;

			case 3:
				*pixel = colors[ 3 ];
				pixel++;
				break;

			default:
				/* invalid */
				pixel++;
				break;
			}
		}
	}
}