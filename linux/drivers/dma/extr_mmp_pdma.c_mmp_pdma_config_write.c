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
typedef  int u32 ;
struct mmp_pdma_chan {int dcmd; int dir; int dev_addr; scalar_t__ drcmr; } ;
struct dma_slave_config {int src_maxburst; int src_addr_width; int src_addr; int dst_maxburst; int dst_addr_width; int dst_addr; scalar_t__ slave_id; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;

/* Variables and functions */
 int DCMD_BURST16 ; 
 int DCMD_BURST32 ; 
 int DCMD_BURST8 ; 
 int DCMD_FLOWSRC ; 
 int DCMD_FLOWTRG ; 
 int DCMD_INCSRCADDR ; 
 int DCMD_INCTRGADDR ; 
 int DCMD_WIDTH1 ; 
 int DCMD_WIDTH2 ; 
 int DCMD_WIDTH4 ; 
 int DMA_DEV_TO_MEM ; 
 int DMA_MEM_TO_DEV ; 
 int DMA_SLAVE_BUSWIDTH_1_BYTE ; 
 int DMA_SLAVE_BUSWIDTH_2_BYTES ; 
 int DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int DMA_SLAVE_BUSWIDTH_UNDEFINED ; 
 int EINVAL ; 
 struct mmp_pdma_chan* to_mmp_pdma_chan (struct dma_chan*) ; 

__attribute__((used)) static int mmp_pdma_config_write(struct dma_chan *dchan,
			   struct dma_slave_config *cfg,
			   enum dma_transfer_direction direction)
{
	struct mmp_pdma_chan *chan = to_mmp_pdma_chan(dchan);
	u32 maxburst = 0, addr = 0;
	enum dma_slave_buswidth width = DMA_SLAVE_BUSWIDTH_UNDEFINED;

	if (!dchan)
		return -EINVAL;

	if (direction == DMA_DEV_TO_MEM) {
		chan->dcmd = DCMD_INCTRGADDR | DCMD_FLOWSRC;
		maxburst = cfg->src_maxburst;
		width = cfg->src_addr_width;
		addr = cfg->src_addr;
	} else if (direction == DMA_MEM_TO_DEV) {
		chan->dcmd = DCMD_INCSRCADDR | DCMD_FLOWTRG;
		maxburst = cfg->dst_maxburst;
		width = cfg->dst_addr_width;
		addr = cfg->dst_addr;
	}

	if (width == DMA_SLAVE_BUSWIDTH_1_BYTE)
		chan->dcmd |= DCMD_WIDTH1;
	else if (width == DMA_SLAVE_BUSWIDTH_2_BYTES)
		chan->dcmd |= DCMD_WIDTH2;
	else if (width == DMA_SLAVE_BUSWIDTH_4_BYTES)
		chan->dcmd |= DCMD_WIDTH4;

	if (maxburst == 8)
		chan->dcmd |= DCMD_BURST8;
	else if (maxburst == 16)
		chan->dcmd |= DCMD_BURST16;
	else if (maxburst == 32)
		chan->dcmd |= DCMD_BURST32;

	chan->dir = direction;
	chan->dev_addr = addr;
	/* FIXME: drivers should be ported over to use the filter
	 * function. Once that's done, the following two lines can
	 * be removed.
	 */
	if (cfg->slave_id)
		chan->drcmr = cfg->slave_id;

	return 0;
}