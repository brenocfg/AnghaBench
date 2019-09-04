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
struct TYPE_3__ {unsigned char* data; } ;
typedef  TYPE_1__ ddsBuffer_t ;

/* Variables and functions */

__attribute__((used)) static int DDSDecompressARGB8888( ddsBuffer_t *dds, int width, int height, unsigned char *pixels ){
	int x, y;
	unsigned char               *in, *out;


	/* setup */
	in = dds->data;
	out = pixels;

	/* walk y */
	for ( y = 0; y < height; y++ )
	{
		/* walk x */
		for ( x = 0; x < width; x++ )
		{
			*out++ = *in++;
			*out++ = *in++;
			*out++ = *in++;
			*out++ = *in++;
		}
	}

	/* return ok */
	return 0;
}