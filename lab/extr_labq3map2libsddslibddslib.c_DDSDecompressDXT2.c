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
typedef  int /*<<< orphan*/  ddsBuffer_t ;

/* Variables and functions */
 int DDSDecompressDXT3 (int /*<<< orphan*/ *,int,int,unsigned char*) ; 

__attribute__((used)) static int DDSDecompressDXT2( ddsBuffer_t *dds, int width, int height, unsigned char *pixels ){
	int r;


	/* decompress dxt3 first */
	r = DDSDecompressDXT3( dds, width, height, pixels );

	/* return to sender */
	return r;
}