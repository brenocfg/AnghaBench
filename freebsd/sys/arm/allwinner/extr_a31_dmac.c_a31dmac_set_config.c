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
typedef  unsigned int uint32_t ;
struct sunxi_dma_config {int dst_width; int dst_burst_len; int src_width; int src_burst_len; unsigned int dst_wait_cyc; unsigned int src_wait_cyc; unsigned int dst_drqtype; unsigned int src_drqtype; scalar_t__ src_noincr; scalar_t__ dst_noincr; } ;
struct a31dmac_channel {TYPE_1__* desc; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {void* para; void* config; } ;

/* Variables and functions */
 unsigned int DMA_ADDR_MODE_IO ; 
 unsigned int DMA_ADDR_MODE_LINEAR ; 
 unsigned int DMA_BST_LEN_1 ; 
 unsigned int DMA_BST_LEN_16 ; 
 unsigned int DMA_BST_LEN_4 ; 
 unsigned int DMA_BST_LEN_8 ; 
 unsigned int DMA_DATA_WIDTH_16BIT ; 
 unsigned int DMA_DATA_WIDTH_32BIT ; 
 unsigned int DMA_DATA_WIDTH_64BIT ; 
 unsigned int DMA_DATA_WIDTH_8BIT ; 
 unsigned int DMA_DEST_ADDR_MODE_SHIFT ; 
 unsigned int DMA_DEST_BST_LEN_SHIFT ; 
 unsigned int DMA_DEST_DATA_WIDTH_SHIFT ; 
 unsigned int DMA_DEST_DRQ_TYPE_SHIFT ; 
 unsigned int DMA_SRC_ADDR_MODE_SHIFT ; 
 unsigned int DMA_SRC_BST_LEN_SHIFT ; 
 unsigned int DMA_SRC_DATA_WIDTH_SHIFT ; 
 unsigned int DMA_SRC_DRQ_TYPE_SHIFT ; 
 int EINVAL ; 
 unsigned int WAIT_CYC_SHIFT ; 
 void* htole32 (unsigned int) ; 

__attribute__((used)) static int
a31dmac_set_config(device_t dev, void *priv, const struct sunxi_dma_config *cfg)
{
	struct a31dmac_channel *ch;
	uint32_t config, para;
	unsigned int dst_dw, dst_bl, dst_wc, dst_am;
	unsigned int src_dw, src_bl, src_wc, src_am;

	ch = priv;

	switch (cfg->dst_width) {
	case 8:
		dst_dw = DMA_DATA_WIDTH_8BIT;
		break;
	case 16:
		dst_dw = DMA_DATA_WIDTH_16BIT;
		break;
	case 32:
		dst_dw = DMA_DATA_WIDTH_32BIT;
		break;
	case 64:
		dst_dw = DMA_DATA_WIDTH_64BIT;
		break;
	default:
		return (EINVAL);
	}
	switch (cfg->dst_burst_len) {
	case 1:
		dst_bl = DMA_BST_LEN_1;
		break;
	case 4:
		dst_bl = DMA_BST_LEN_4;
		break;
	case 8:
		dst_bl = DMA_BST_LEN_8;
		break;
	case 16:
		dst_bl = DMA_BST_LEN_16;
		break;
	default:
		return (EINVAL);
	}
	switch (cfg->src_width) {
	case 8:
		src_dw = DMA_DATA_WIDTH_8BIT;
		break;
	case 16:
		src_dw = DMA_DATA_WIDTH_16BIT;
		break;
	case 32:
		src_dw = DMA_DATA_WIDTH_32BIT;
		break;
	case 64:
		src_dw = DMA_DATA_WIDTH_64BIT;
	default:
		return (EINVAL);
	}
	switch (cfg->src_burst_len) {
	case 1:
		src_bl = DMA_BST_LEN_1;
		break;
	case 4:
		src_bl = DMA_BST_LEN_4;
		break;
	case 8:
		src_bl = DMA_BST_LEN_8;
		break;
	case 16:
		src_bl = DMA_BST_LEN_16;
		break;
	default:
		return (EINVAL);
	}
	dst_am = cfg->dst_noincr ? DMA_ADDR_MODE_IO : DMA_ADDR_MODE_LINEAR;
	src_am = cfg->src_noincr ? DMA_ADDR_MODE_IO : DMA_ADDR_MODE_LINEAR;
	dst_wc = cfg->dst_wait_cyc;
	src_wc = cfg->src_wait_cyc;
	if (dst_wc != src_wc)
		return (EINVAL);

	config = (dst_dw << DMA_DEST_DATA_WIDTH_SHIFT) |
		 (dst_bl << DMA_DEST_BST_LEN_SHIFT) |
		 (dst_am << DMA_DEST_ADDR_MODE_SHIFT) |
		 (cfg->dst_drqtype << DMA_DEST_DRQ_TYPE_SHIFT) |
		 (src_dw << DMA_SRC_DATA_WIDTH_SHIFT) |
		 (src_bl << DMA_SRC_BST_LEN_SHIFT) |
		 (src_am << DMA_SRC_ADDR_MODE_SHIFT) |
		 (cfg->src_drqtype << DMA_SRC_DRQ_TYPE_SHIFT);
	para = (dst_wc << WAIT_CYC_SHIFT);

	ch->desc->config = htole32(config);
	ch->desc->para = htole32(para);

	return (0);
}