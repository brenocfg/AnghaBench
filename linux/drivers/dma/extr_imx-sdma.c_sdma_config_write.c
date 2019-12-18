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
struct sdma_channel {int watermark_level; int word_size; int direction; int /*<<< orphan*/  per_address; int /*<<< orphan*/  per_address2; } ;
struct dma_slave_config {int src_maxburst; int src_addr_width; int dst_maxburst; int dst_addr_width; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;

/* Variables and functions */
 int DMA_DEV_TO_DEV ; 
 int DMA_DEV_TO_MEM ; 
 int SDMA_WATERMARK_LEVEL_HWML ; 
 int SDMA_WATERMARK_LEVEL_LWML ; 
 int sdma_config_channel (struct dma_chan*) ; 
 struct sdma_channel* to_sdma_chan (struct dma_chan*) ; 

__attribute__((used)) static int sdma_config_write(struct dma_chan *chan,
		       struct dma_slave_config *dmaengine_cfg,
		       enum dma_transfer_direction direction)
{
	struct sdma_channel *sdmac = to_sdma_chan(chan);

	if (direction == DMA_DEV_TO_MEM) {
		sdmac->per_address = dmaengine_cfg->src_addr;
		sdmac->watermark_level = dmaengine_cfg->src_maxburst *
			dmaengine_cfg->src_addr_width;
		sdmac->word_size = dmaengine_cfg->src_addr_width;
	} else if (direction == DMA_DEV_TO_DEV) {
		sdmac->per_address2 = dmaengine_cfg->src_addr;
		sdmac->per_address = dmaengine_cfg->dst_addr;
		sdmac->watermark_level = dmaengine_cfg->src_maxburst &
			SDMA_WATERMARK_LEVEL_LWML;
		sdmac->watermark_level |= (dmaengine_cfg->dst_maxburst << 16) &
			SDMA_WATERMARK_LEVEL_HWML;
		sdmac->word_size = dmaengine_cfg->dst_addr_width;
	} else {
		sdmac->per_address = dmaengine_cfg->dst_addr;
		sdmac->watermark_level = dmaengine_cfg->dst_maxburst *
			dmaengine_cfg->dst_addr_width;
		sdmac->word_size = dmaengine_cfg->dst_addr_width;
	}
	sdmac->direction = direction;
	return sdma_config_channel(chan);
}