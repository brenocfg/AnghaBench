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
struct imxdma_engine {int dummy; } ;
struct imxdma_channel {int watermark_level; int word_size; unsigned int ccr_from_device; int ccr_to_device; int dma_request; int /*<<< orphan*/  channel; scalar_t__ hw_chaining; int /*<<< orphan*/  per_address; struct imxdma_engine* imxdma; } ;
struct dma_slave_config {int src_maxburst; int src_addr_width; int dst_maxburst; int dst_addr_width; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;

/* Variables and functions */
 unsigned int CCR_REN ; 
 int /*<<< orphan*/  DMA_BLR (int /*<<< orphan*/ ) ; 
 int DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_RSSR (int /*<<< orphan*/ ) ; 
#define  DMA_SLAVE_BUSWIDTH_1_BYTE 130 
#define  DMA_SLAVE_BUSWIDTH_2_BYTES 129 
#define  DMA_SLAVE_BUSWIDTH_4_BYTES 128 
 unsigned int IMX_DMA_MEMSIZE_16 ; 
 int IMX_DMA_MEMSIZE_32 ; 
 unsigned int IMX_DMA_MEMSIZE_8 ; 
 unsigned int IMX_DMA_TYPE_FIFO ; 
 int IMX_DMA_TYPE_LINEAR ; 
 int /*<<< orphan*/  imx_dmav1_writel (struct imxdma_engine*,int,int /*<<< orphan*/ ) ; 
 struct imxdma_channel* to_imxdma_chan (struct dma_chan*) ; 

__attribute__((used)) static int imxdma_config_write(struct dma_chan *chan,
			       struct dma_slave_config *dmaengine_cfg,
			       enum dma_transfer_direction direction)
{
	struct imxdma_channel *imxdmac = to_imxdma_chan(chan);
	struct imxdma_engine *imxdma = imxdmac->imxdma;
	unsigned int mode = 0;

	if (direction == DMA_DEV_TO_MEM) {
		imxdmac->per_address = dmaengine_cfg->src_addr;
		imxdmac->watermark_level = dmaengine_cfg->src_maxburst;
		imxdmac->word_size = dmaengine_cfg->src_addr_width;
	} else {
		imxdmac->per_address = dmaengine_cfg->dst_addr;
		imxdmac->watermark_level = dmaengine_cfg->dst_maxburst;
		imxdmac->word_size = dmaengine_cfg->dst_addr_width;
	}

	switch (imxdmac->word_size) {
	case DMA_SLAVE_BUSWIDTH_1_BYTE:
		mode = IMX_DMA_MEMSIZE_8;
		break;
	case DMA_SLAVE_BUSWIDTH_2_BYTES:
		mode = IMX_DMA_MEMSIZE_16;
		break;
	default:
	case DMA_SLAVE_BUSWIDTH_4_BYTES:
		mode = IMX_DMA_MEMSIZE_32;
		break;
	}

	imxdmac->hw_chaining = 0;

	imxdmac->ccr_from_device = (mode | IMX_DMA_TYPE_FIFO) |
		((IMX_DMA_MEMSIZE_32 | IMX_DMA_TYPE_LINEAR) << 2) |
		CCR_REN;
	imxdmac->ccr_to_device =
		(IMX_DMA_MEMSIZE_32 | IMX_DMA_TYPE_LINEAR) |
		((mode | IMX_DMA_TYPE_FIFO) << 2) | CCR_REN;
	imx_dmav1_writel(imxdma, imxdmac->dma_request,
			 DMA_RSSR(imxdmac->channel));

	/* Set burst length */
	imx_dmav1_writel(imxdma, imxdmac->watermark_level *
			 imxdmac->word_size, DMA_BLR(imxdmac->channel));

	return 0;
}