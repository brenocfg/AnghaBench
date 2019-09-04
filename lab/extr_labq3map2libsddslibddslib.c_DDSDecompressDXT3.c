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
struct TYPE_5__ {int r; int g; int b; scalar_t__ a; } ;
typedef  TYPE_1__ ddsColor_t ;
typedef  int /*<<< orphan*/  ddsColorBlock_t ;
struct TYPE_6__ {scalar_t__ data; } ;
typedef  TYPE_2__ ddsBuffer_t ;
typedef  int /*<<< orphan*/  ddsAlphaBlockExplicit_t ;

/* Variables and functions */
 int /*<<< orphan*/  DDSDecodeAlphaExplicit (unsigned int*,int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/  DDSDecodeColorBlock (unsigned int*,int /*<<< orphan*/ *,int,unsigned int*) ; 
 int /*<<< orphan*/  DDSGetColorBlockColors (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int DDSDecompressDXT3( ddsBuffer_t *dds, int width, int height, unsigned char *pixels ){
	int x, y, xBlocks, yBlocks;
	unsigned int            *pixel, alphaZero;
	ddsColorBlock_t         *block;
	ddsAlphaBlockExplicit_t *alphaBlock;
	ddsColor_t colors[ 4 ];


	/* setup */
	xBlocks = width / 4;
	yBlocks = height / 4;

	/* create zero alpha */
	colors[ 0 ].a = 0;
	colors[ 0 ].r = 0xFF;
	colors[ 0 ].g = 0xFF;
	colors[ 0 ].b = 0xFF;
	alphaZero = *( (unsigned int*) &colors[ 0 ] );

	/* walk y */
	for ( y = 0; y < yBlocks; y++ )
	{
		/* 8 bytes per block, 1 block for alpha, 1 block for color */
		block = (ddsColorBlock_t*) ( (size_t) dds->data + y * xBlocks * 16 );

		/* walk x */
		for ( x = 0; x < xBlocks; x++, block++ )
		{
			/* get alpha block */
			alphaBlock = (ddsAlphaBlockExplicit_t*) block;

			/* get color block */
			block++;
			DDSGetColorBlockColors( block, colors );

			/* decode color block */
			pixel = (unsigned int*) ( pixels + x * 16 + ( y * 4 ) * width * 4 );
			DDSDecodeColorBlock( pixel, block, width, (unsigned int*) colors );

			/* overwrite alpha bits with alpha block */
			DDSDecodeAlphaExplicit( pixel, alphaBlock, width, alphaZero );
		}
	}

	/* return ok */
	return 0;
}