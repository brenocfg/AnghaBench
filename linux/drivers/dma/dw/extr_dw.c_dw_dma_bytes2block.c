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
typedef  size_t u32 ;
struct dw_dma_chan {size_t block_size; } ;

/* Variables and functions */

__attribute__((used)) static u32 dw_dma_bytes2block(struct dw_dma_chan *dwc,
			      size_t bytes, unsigned int width, size_t *len)
{
	u32 block;

	if ((bytes >> width) > dwc->block_size) {
		block = dwc->block_size;
		*len = dwc->block_size << width;
	} else {
		block = bytes >> width;
		*len = bytes;
	}

	return block;
}