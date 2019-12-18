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
typedef  int /*<<< orphan*/  ddsColor_t ;
typedef  int /*<<< orphan*/  ddsColorBlock_t ;
struct TYPE_3__ {scalar_t__ data; } ;
typedef  TYPE_1__ ddsBuffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  DDSDecodeColorBlock (unsigned int*,int /*<<< orphan*/ *,int,unsigned int*) ; 
 int /*<<< orphan*/  DDSGetColorBlockColors (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int DDSDecompressDXT1( ddsBuffer_t *dds, int width, int height, unsigned char *pixels ){
	int x, y, xBlocks, yBlocks;
	unsigned int    *pixel;
	ddsColorBlock_t *block;
	ddsColor_t colors[ 4 ];


	/* setup */
	xBlocks = width / 4;
	yBlocks = height / 4;

	/* walk y */
	for ( y = 0; y < yBlocks; y++ )
	{
		/* 8 bytes per block */
		block = (ddsColorBlock_t*) ( (size_t) dds->data + y * xBlocks * 8 );

		/* walk x */
		for ( x = 0; x < xBlocks; x++, block++ )
		{
			DDSGetColorBlockColors( block, colors );
			pixel = (unsigned int*) ( pixels + x * 16 + ( y * 4 ) * width * 4 );
			DDSDecodeColorBlock( pixel, block, width, (unsigned int*) colors );
		}
	}

	/* return ok */
	return 0;
}