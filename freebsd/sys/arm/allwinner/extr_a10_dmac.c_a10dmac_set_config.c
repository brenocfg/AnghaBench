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
typedef  unsigned int uint32_t ;
struct sunxi_dma_config {int dst_width; int dst_burst_len; int src_width; int src_burst_len; unsigned int dst_drqtype; unsigned int src_drqtype; int dst_blksize; int dst_wait_cyc; int src_blksize; int src_wait_cyc; scalar_t__ src_noincr; scalar_t__ dst_noincr; } ;
struct a10dmac_channel {scalar_t__ ch_type; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 unsigned int AWIN_DDMA_CTL_DMA_ADDR_IO ; 
 unsigned int AWIN_DDMA_CTL_DMA_ADDR_LINEAR ; 
 unsigned int AWIN_DDMA_CTL_DST_ADDR_MODE_SHIFT ; 
 int /*<<< orphan*/  AWIN_DDMA_CTL_REG ; 
 unsigned int AWIN_DDMA_CTL_SRC_ADDR_MODE_SHIFT ; 
 unsigned int AWIN_DDMA_PARA_DST_DATA_BLK_SIZ_SHIFT ; 
 unsigned int AWIN_DDMA_PARA_DST_WAIT_CYC_SHIFT ; 
 int /*<<< orphan*/  AWIN_DDMA_PARA_REG ; 
 unsigned int AWIN_DDMA_PARA_SRC_DATA_BLK_SIZ_SHIFT ; 
 unsigned int AWIN_DDMA_PARA_SRC_WAIT_CYC_SHIFT ; 
 unsigned int AWIN_DMA_CTL_BURST_LEN_1 ; 
 unsigned int AWIN_DMA_CTL_BURST_LEN_4 ; 
 unsigned int AWIN_DMA_CTL_BURST_LEN_8 ; 
 unsigned int AWIN_DMA_CTL_DATA_WIDTH_16 ; 
 unsigned int AWIN_DMA_CTL_DATA_WIDTH_32 ; 
 unsigned int AWIN_DMA_CTL_DATA_WIDTH_8 ; 
 unsigned int AWIN_DMA_CTL_DST_BURST_LEN_SHIFT ; 
 unsigned int AWIN_DMA_CTL_DST_DATA_WIDTH_SHIFT ; 
 unsigned int AWIN_DMA_CTL_DST_DRQ_TYPE_SHIFT ; 
 unsigned int AWIN_DMA_CTL_SRC_BURST_LEN_SHIFT ; 
 unsigned int AWIN_DMA_CTL_SRC_DATA_WIDTH_SHIFT ; 
 unsigned int AWIN_DMA_CTL_SRC_DRQ_TYPE_SHIFT ; 
 unsigned int AWIN_NDMA_CTL_DST_ADDR_NOINCR ; 
 int /*<<< orphan*/  AWIN_NDMA_CTL_REG ; 
 unsigned int AWIN_NDMA_CTL_SRC_ADDR_NOINCR ; 
 scalar_t__ CH_NDMA ; 
 int /*<<< orphan*/  DMACH_WRITE (struct a10dmac_channel*,int /*<<< orphan*/ ,unsigned int) ; 
 int EINVAL ; 

__attribute__((used)) static int
a10dmac_set_config(device_t dev, void *priv, const struct sunxi_dma_config *cfg)
{
	struct a10dmac_channel *ch = priv;
	uint32_t val;
	unsigned int dst_dw, dst_bl, dst_bs, dst_wc, dst_am;
	unsigned int src_dw, src_bl, src_bs, src_wc, src_am;

	switch (cfg->dst_width) {
	case 8:
		dst_dw = AWIN_DMA_CTL_DATA_WIDTH_8;
		break;
	case 16:
		dst_dw = AWIN_DMA_CTL_DATA_WIDTH_16;
		break;
	case 32:
		dst_dw = AWIN_DMA_CTL_DATA_WIDTH_32;
		break;
	default:
		return (EINVAL);
	}
	switch (cfg->dst_burst_len) {
	case 1:
		dst_bl = AWIN_DMA_CTL_BURST_LEN_1;
		break;
	case 4:
		dst_bl = AWIN_DMA_CTL_BURST_LEN_4;
		break;
	case 8:
		dst_bl = AWIN_DMA_CTL_BURST_LEN_8;
		break;
	default:
		return (EINVAL);
	}
	switch (cfg->src_width) {
	case 8:
		src_dw = AWIN_DMA_CTL_DATA_WIDTH_8;
		break;
	case 16:
		src_dw = AWIN_DMA_CTL_DATA_WIDTH_16;
		break;
	case 32:
		src_dw = AWIN_DMA_CTL_DATA_WIDTH_32;
		break;
	default:
		return (EINVAL);
	}
	switch (cfg->src_burst_len) {
	case 1:
		src_bl = AWIN_DMA_CTL_BURST_LEN_1;
		break;
	case 4:
		src_bl = AWIN_DMA_CTL_BURST_LEN_4;
		break;
	case 8:
		src_bl = AWIN_DMA_CTL_BURST_LEN_8;
		break;
	default:
		return (EINVAL);
	}

	val = (dst_dw << AWIN_DMA_CTL_DST_DATA_WIDTH_SHIFT) |
	      (dst_bl << AWIN_DMA_CTL_DST_BURST_LEN_SHIFT) |
	      (cfg->dst_drqtype << AWIN_DMA_CTL_DST_DRQ_TYPE_SHIFT) |
	      (src_dw << AWIN_DMA_CTL_SRC_DATA_WIDTH_SHIFT) |
	      (src_bl << AWIN_DMA_CTL_SRC_BURST_LEN_SHIFT) |
	      (cfg->src_drqtype << AWIN_DMA_CTL_SRC_DRQ_TYPE_SHIFT);

	if (ch->ch_type == CH_NDMA) {
		if (cfg->dst_noincr)
			val |= AWIN_NDMA_CTL_DST_ADDR_NOINCR;
		if (cfg->src_noincr)
			val |= AWIN_NDMA_CTL_SRC_ADDR_NOINCR;

		DMACH_WRITE(ch, AWIN_NDMA_CTL_REG, val);
	} else {
		dst_am = cfg->dst_noincr ? AWIN_DDMA_CTL_DMA_ADDR_IO :
		    AWIN_DDMA_CTL_DMA_ADDR_LINEAR;
		src_am = cfg->src_noincr ? AWIN_DDMA_CTL_DMA_ADDR_IO :
		    AWIN_DDMA_CTL_DMA_ADDR_LINEAR;

		val |= (dst_am << AWIN_DDMA_CTL_DST_ADDR_MODE_SHIFT);
		val |= (src_am << AWIN_DDMA_CTL_SRC_ADDR_MODE_SHIFT);

		DMACH_WRITE(ch, AWIN_DDMA_CTL_REG, val);

		dst_bs = cfg->dst_blksize - 1;
		dst_wc = cfg->dst_wait_cyc - 1;
		src_bs = cfg->src_blksize - 1;
		src_wc = cfg->src_wait_cyc - 1;

		DMACH_WRITE(ch, AWIN_DDMA_PARA_REG,
		    (dst_bs << AWIN_DDMA_PARA_DST_DATA_BLK_SIZ_SHIFT) |
		    (dst_wc << AWIN_DDMA_PARA_DST_WAIT_CYC_SHIFT) |
		    (src_bs << AWIN_DDMA_PARA_SRC_DATA_BLK_SIZ_SHIFT) |
		    (src_wc << AWIN_DDMA_PARA_SRC_WAIT_CYC_SHIFT));
	}

	return (0);
}