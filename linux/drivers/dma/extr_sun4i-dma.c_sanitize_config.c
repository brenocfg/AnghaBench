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
struct dma_slave_config {int /*<<< orphan*/  src_maxburst; int /*<<< orphan*/  dst_maxburst; int /*<<< orphan*/  src_addr_width; int /*<<< orphan*/  dst_addr_width; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;

/* Variables and functions */
#define  DMA_DEV_TO_MEM 129 
#define  DMA_MEM_TO_DEV 128 
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_UNDEFINED ; 
 int EINVAL ; 

__attribute__((used)) static int sanitize_config(struct dma_slave_config *sconfig,
			   enum dma_transfer_direction direction)
{
	switch (direction) {
	case DMA_MEM_TO_DEV:
		if ((sconfig->dst_addr_width == DMA_SLAVE_BUSWIDTH_UNDEFINED) ||
		    !sconfig->dst_maxburst)
			return -EINVAL;

		if (sconfig->src_addr_width == DMA_SLAVE_BUSWIDTH_UNDEFINED)
			sconfig->src_addr_width = sconfig->dst_addr_width;

		if (!sconfig->src_maxburst)
			sconfig->src_maxburst = sconfig->dst_maxburst;

		break;

	case DMA_DEV_TO_MEM:
		if ((sconfig->src_addr_width == DMA_SLAVE_BUSWIDTH_UNDEFINED) ||
		    !sconfig->src_maxburst)
			return -EINVAL;

		if (sconfig->dst_addr_width == DMA_SLAVE_BUSWIDTH_UNDEFINED)
			sconfig->dst_addr_width = sconfig->src_addr_width;

		if (!sconfig->dst_maxburst)
			sconfig->dst_maxburst = sconfig->src_maxburst;

		break;
	default:
		return 0;
	}

	return 0;
}