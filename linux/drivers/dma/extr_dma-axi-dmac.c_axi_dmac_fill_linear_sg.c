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
struct axi_dmac_sg {unsigned int dest_addr; unsigned int src_addr; unsigned int x_len; int y_len; } ;
struct axi_dmac_chan {unsigned int max_length; unsigned int length_align_mask; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  unsigned int dma_addr_t ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 int DMA_DEV_TO_MEM ; 

__attribute__((used)) static struct axi_dmac_sg *axi_dmac_fill_linear_sg(struct axi_dmac_chan *chan,
	enum dma_transfer_direction direction, dma_addr_t addr,
	unsigned int num_periods, unsigned int period_len,
	struct axi_dmac_sg *sg)
{
	unsigned int num_segments, i;
	unsigned int segment_size;
	unsigned int len;

	/* Split into multiple equally sized segments if necessary */
	num_segments = DIV_ROUND_UP(period_len, chan->max_length);
	segment_size = DIV_ROUND_UP(period_len, num_segments);
	/* Take care of alignment */
	segment_size = ((segment_size - 1) | chan->length_align_mask) + 1;

	for (i = 0; i < num_periods; i++) {
		len = period_len;

		while (len > segment_size) {
			if (direction == DMA_DEV_TO_MEM)
				sg->dest_addr = addr;
			else
				sg->src_addr = addr;
			sg->x_len = segment_size;
			sg->y_len = 1;
			sg++;
			addr += segment_size;
			len -= segment_size;
		}

		if (direction == DMA_DEV_TO_MEM)
			sg->dest_addr = addr;
		else
			sg->src_addr = addr;
		sg->x_len = len;
		sg->y_len = 1;
		sg++;
		addr += len;
	}

	return sg;
}