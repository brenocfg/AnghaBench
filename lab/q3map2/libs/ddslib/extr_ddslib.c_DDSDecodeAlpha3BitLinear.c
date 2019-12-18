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
struct TYPE_4__ {unsigned char a; scalar_t__ b; scalar_t__ g; scalar_t__ r; } ;
typedef  TYPE_1__ ddsColor_t ;
struct TYPE_5__ {unsigned short alpha0; unsigned short alpha1; int /*<<< orphan*/ * stuff; } ;
typedef  TYPE_2__ ddsAlphaBlock3BitLinear_t ;

/* Variables and functions */

__attribute__((used)) static void DDSDecodeAlpha3BitLinear( unsigned int *pixel, ddsAlphaBlock3BitLinear_t *alphaBlock, int width, unsigned int alphaZero ){

	int row, pix;
	unsigned int stuff;
	unsigned char bits[ 4 ][ 4 ];
	unsigned short alphas[ 8 ];
	ddsColor_t aColors[ 4 ][ 4 ];


	/* get initial alphas */
	alphas[ 0 ] = alphaBlock->alpha0;
	alphas[ 1 ] = alphaBlock->alpha1;

	/* 8-alpha block */
	if ( alphas[ 0 ] > alphas[ 1 ] ) {
		/* 000 = alpha_0, 001 = alpha_1, others are interpolated */
		alphas[ 2 ] = ( 6 * alphas[ 0 ] +     alphas[ 1 ] ) / 7; /* bit code 010 */
		alphas[ 3 ] = ( 5 * alphas[ 0 ] + 2 * alphas[ 1 ] ) / 7; /* bit code 011 */
		alphas[ 4 ] = ( 4 * alphas[ 0 ] + 3 * alphas[ 1 ] ) / 7; /* bit code 100 */
		alphas[ 5 ] = ( 3 * alphas[ 0 ] + 4 * alphas[ 1 ] ) / 7; /* bit code 101 */
		alphas[ 6 ] = ( 2 * alphas[ 0 ] + 5 * alphas[ 1 ] ) / 7; /* bit code 110 */
		alphas[ 7 ] = (     alphas[ 0 ] + 6 * alphas[ 1 ] ) / 7; /* bit code 111 */
	}

	/* 6-alpha block */
	else
	{
		/* 000 = alpha_0, 001 = alpha_1, others are interpolated */
		alphas[ 2 ] = ( 4 * alphas[ 0 ] +     alphas[ 1 ] ) / 5;  /* bit code 010 */
		alphas[ 3 ] = ( 3 * alphas[ 0 ] + 2 * alphas[ 1 ] ) / 5;  /* bit code 011 */
		alphas[ 4 ] = ( 2 * alphas[ 0 ] + 3 * alphas[ 1 ] ) / 5;  /* bit code 100 */
		alphas[ 5 ] = (    alphas[ 0 ] + 4 * alphas[ 1 ] ) / 5;  /* bit code 101 */
		alphas[ 6 ] = 0;                                        /* bit code 110 */
		alphas[ 7 ] = 255;                                      /* bit code 111 */
	}

	/* decode 3-bit fields into array of 16 bytes with same value */

	/* first two rows of 4 pixels each */
	stuff = *( (unsigned int*) &( alphaBlock->stuff[ 0 ] ) );

	bits[ 0 ][ 0 ] = (unsigned char) ( stuff & 0x00000007 );
	stuff >>= 3;
	bits[ 0 ][ 1 ] = (unsigned char) ( stuff & 0x00000007 );
	stuff >>= 3;
	bits[ 0 ][ 2 ] = (unsigned char) ( stuff & 0x00000007 );
	stuff >>= 3;
	bits[ 0 ][ 3 ] = (unsigned char) ( stuff & 0x00000007 );
	stuff >>= 3;
	bits[ 1 ][ 0 ] = (unsigned char) ( stuff & 0x00000007 );
	stuff >>= 3;
	bits[ 1 ][ 1 ] = (unsigned char) ( stuff & 0x00000007 );
	stuff >>= 3;
	bits[ 1 ][ 2 ] = (unsigned char) ( stuff & 0x00000007 );
	stuff >>= 3;
	bits[ 1 ][ 3 ] = (unsigned char) ( stuff & 0x00000007 );

	/* last two rows */
	stuff = *( (unsigned int*) &( alphaBlock->stuff[ 3 ] ) ); /* last 3 bytes */

	bits[ 2 ][ 0 ] = (unsigned char) ( stuff & 0x00000007 );
	stuff >>= 3;
	bits[ 2 ][ 1 ] = (unsigned char) ( stuff & 0x00000007 );
	stuff >>= 3;
	bits[ 2 ][ 2 ] = (unsigned char) ( stuff & 0x00000007 );
	stuff >>= 3;
	bits[ 2 ][ 3 ] = (unsigned char) ( stuff & 0x00000007 );
	stuff >>= 3;
	bits[ 3 ][ 0 ] = (unsigned char) ( stuff & 0x00000007 );
	stuff >>= 3;
	bits[ 3 ][ 1 ] = (unsigned char) ( stuff & 0x00000007 );
	stuff >>= 3;
	bits[ 3 ][ 2 ] = (unsigned char) ( stuff & 0x00000007 );
	stuff >>= 3;
	bits[ 3 ][ 3 ] = (unsigned char) ( stuff & 0x00000007 );

	/* decode the codes into alpha values */
	for ( row = 0; row < 4; row++ )
	{
		for ( pix = 0; pix < 4; pix++ )
		{
			aColors[ row ][ pix ].r = 0;
			aColors[ row ][ pix ].g = 0;
			aColors[ row ][ pix ].b = 0;
			aColors[ row ][ pix ].a = (unsigned char) alphas[ bits[ row ][ pix ] ];
		}
	}

	/* write out alpha values to the image bits */
	for ( row = 0; row < 4; row++, pixel += width - 4 )
	{
		for ( pix = 0; pix < 4; pix++ )
		{
			/* zero the alpha bits of image pixel */
			*pixel &= alphaZero;

			/* or the bits into the prev. nulled alpha */
			*pixel |= *( (unsigned int*) &( aColors[ row ][ pix ] ) );
			pixel++;
		}
	}
}