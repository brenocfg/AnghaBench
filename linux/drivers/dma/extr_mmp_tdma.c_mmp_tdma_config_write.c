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
struct mmp_tdma_chan {int dir; int /*<<< orphan*/  buswidth; int /*<<< orphan*/  burst_sz; int /*<<< orphan*/  dev_addr; } ;
struct dma_slave_config {int /*<<< orphan*/  dst_addr_width; int /*<<< orphan*/  dst_maxburst; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr_width; int /*<<< orphan*/  src_maxburst; int /*<<< orphan*/  src_addr; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;

/* Variables and functions */
 int DMA_DEV_TO_MEM ; 
 int mmp_tdma_config_chan (struct dma_chan*) ; 
 struct mmp_tdma_chan* to_mmp_tdma_chan (struct dma_chan*) ; 

__attribute__((used)) static int mmp_tdma_config_write(struct dma_chan *chan,
				 enum dma_transfer_direction dir,
				 struct dma_slave_config *dmaengine_cfg)
{
	struct mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);

	if (dir == DMA_DEV_TO_MEM) {
		tdmac->dev_addr = dmaengine_cfg->src_addr;
		tdmac->burst_sz = dmaengine_cfg->src_maxburst;
		tdmac->buswidth = dmaengine_cfg->src_addr_width;
	} else {
		tdmac->dev_addr = dmaengine_cfg->dst_addr;
		tdmac->burst_sz = dmaengine_cfg->dst_maxburst;
		tdmac->buswidth = dmaengine_cfg->dst_addr_width;
	}
	tdmac->dir = dir;

	return mmp_tdma_config_chan(chan);
}