#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int a; unsigned char b; unsigned char g; unsigned char r; } ;
typedef  TYPE_1__ ddsColor_t ;
struct TYPE_6__ {scalar_t__* colors; } ;
typedef  TYPE_2__ ddsColorBlock_t ;

/* Variables and functions */
 unsigned short DDSLittleShort (scalar_t__) ; 

__attribute__((used)) static void DDSGetColorBlockColors( ddsColorBlock_t *block, ddsColor_t colors[ 4 ] ){
	unsigned short word;


	/* color 0 */
	word = DDSLittleShort( block->colors[ 0 ] );
	colors[ 0 ].a = 0xff;

	/* extract rgb bits */
	colors[ 0 ].b = (unsigned char) word;
	colors[ 0 ].b <<= 3;
	colors[ 0 ].b |= ( colors[ 0 ].b >> 5 );
	word >>= 5;
	colors[ 0 ].g = (unsigned char) word;
	colors[ 0 ].g <<= 2;
	colors[ 0 ].g |= ( colors[ 0 ].g >> 5 );
	word >>= 6;
	colors[ 0 ].r = (unsigned char) word;
	colors[ 0 ].r <<= 3;
	colors[ 0 ].r |= ( colors[ 0 ].r >> 5 );

	/* same for color 1 */
	word = DDSLittleShort( block->colors[ 1 ] );
	colors[ 1 ].a = 0xff;

	/* extract rgb bits */
	colors[ 1 ].b = (unsigned char) word;
	colors[ 1 ].b <<= 3;
	colors[ 1 ].b |= ( colors[ 1 ].b >> 5 );
	word >>= 5;
	colors[ 1 ].g = (unsigned char) word;
	colors[ 1 ].g <<= 2;
	colors[ 1 ].g |= ( colors[ 1 ].g >> 5 );
	word >>= 6;
	colors[ 1 ].r = (unsigned char) word;
	colors[ 1 ].r <<= 3;
	colors[ 1 ].r |= ( colors[ 1 ].r >> 5 );

	/* use this for all but the super-freak math method */
	if ( block->colors[ 0 ] > block->colors[ 1 ] ) {
		/* four-color block: derive the other two colors.
		   00 = color 0, 01 = color 1, 10 = color 2, 11 = color 3
		   these two bit codes correspond to the 2-bit fields
		   stored in the 64-bit block. */

		word = ( (unsigned short) colors[ 0 ].r * 2 + (unsigned short) colors[ 1 ].r ) / 3;
		/* no +1 for rounding */
		/* as bits have been shifted to 888 */
		colors[ 2 ].r = (unsigned char) word;
		word = ( (unsigned short) colors[ 0 ].g * 2 + (unsigned short) colors[ 1 ].g ) / 3;
		colors[ 2 ].g = (unsigned char) word;
		word = ( (unsigned short) colors[ 0 ].b * 2 + (unsigned short) colors[ 1 ].b ) / 3;
		colors[ 2 ].b = (unsigned char) word;
		colors[ 2 ].a = 0xff;

		word = ( (unsigned short) colors[ 0 ].r + (unsigned short) colors[ 1 ].r * 2 ) / 3;
		colors[ 3 ].r = (unsigned char) word;
		word = ( (unsigned short) colors[ 0 ].g + (unsigned short) colors[ 1 ].g * 2 ) / 3;
		colors[ 3 ].g = (unsigned char) word;
		word = ( (unsigned short) colors[ 0 ].b + (unsigned short) colors[ 1 ].b * 2 ) / 3;
		colors[ 3 ].b = (unsigned char) word;
		colors[ 3 ].a = 0xff;
	}
	else
	{
		/* three-color block: derive the other color.
		   00 = color 0, 01 = color 1, 10 = color 2,
		   11 = transparent.
		   These two bit codes correspond to the 2-bit fields
		   stored in the 64-bit block */

		word = ( (unsigned short) colors[ 0 ].r + (unsigned short) colors[ 1 ].r ) / 2;
		colors[ 2 ].r = (unsigned char) word;
		word = ( (unsigned short) colors[ 0 ].g + (unsigned short) colors[ 1 ].g ) / 2;
		colors[ 2 ].g = (unsigned char) word;
		word = ( (unsigned short) colors[ 0 ].b + (unsigned short) colors[ 1 ].b ) / 2;
		colors[ 2 ].b = (unsigned char) word;
		colors[ 2 ].a = 0xff;

		/* random color to indicate alpha */
		colors[ 3 ].r = 0x00;
		colors[ 3 ].g = 0xff;
		colors[ 3 ].b = 0xff;
		colors[ 3 ].a = 0x00;
	}
}