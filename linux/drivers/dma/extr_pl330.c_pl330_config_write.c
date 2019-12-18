#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dma_slave_config {int /*<<< orphan*/  src_maxburst; scalar_t__ src_addr_width; scalar_t__ src_addr; int /*<<< orphan*/  dst_maxburst; scalar_t__ dst_addr_width; scalar_t__ dst_addr; } ;
struct dma_pl330_chan {TYPE_1__* dmac; void* burst_len; void* burst_sz; scalar_t__ fifo_addr; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
struct TYPE_2__ {int /*<<< orphan*/  quirks; } ;

/* Variables and functions */
 int DMA_DEV_TO_MEM ; 
 int DMA_MEM_TO_DEV ; 
 void* __ffs (scalar_t__) ; 
 void* fixup_burst_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl330_unprep_slave_fifo (struct dma_pl330_chan*) ; 
 struct dma_pl330_chan* to_pchan (struct dma_chan*) ; 

__attribute__((used)) static int pl330_config_write(struct dma_chan *chan,
			struct dma_slave_config *slave_config,
			enum dma_transfer_direction direction)
{
	struct dma_pl330_chan *pch = to_pchan(chan);

	pl330_unprep_slave_fifo(pch);
	if (direction == DMA_MEM_TO_DEV) {
		if (slave_config->dst_addr)
			pch->fifo_addr = slave_config->dst_addr;
		if (slave_config->dst_addr_width)
			pch->burst_sz = __ffs(slave_config->dst_addr_width);
		pch->burst_len = fixup_burst_len(slave_config->dst_maxburst,
			pch->dmac->quirks);
	} else if (direction == DMA_DEV_TO_MEM) {
		if (slave_config->src_addr)
			pch->fifo_addr = slave_config->src_addr;
		if (slave_config->src_addr_width)
			pch->burst_sz = __ffs(slave_config->src_addr_width);
		pch->burst_len = fixup_burst_len(slave_config->src_maxburst,
			pch->dmac->quirks);
	}

	return 0;
}