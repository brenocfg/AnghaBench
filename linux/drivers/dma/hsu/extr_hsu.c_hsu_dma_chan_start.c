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
typedef  int u32 ;
struct hsu_dma_desc {unsigned int nents; unsigned int active; TYPE_1__* sg; } ;
struct dma_slave_config {int dst_maxburst; int dst_addr_width; int src_maxburst; int src_addr_width; } ;
struct hsu_dma_chan {scalar_t__ direction; struct hsu_dma_desc* desc; struct dma_slave_config config; } ;
struct TYPE_2__ {int addr; int len; } ;

/* Variables and functions */
 scalar_t__ DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  HSU_CH_BSR ; 
 int /*<<< orphan*/  HSU_CH_DCR ; 
 int HSU_CH_DCR_CHDI (unsigned int) ; 
 int HSU_CH_DCR_CHEI ; 
 int HSU_CH_DCR_CHSOD (unsigned int) ; 
 int HSU_CH_DCR_CHSOE ; 
 int HSU_CH_DCR_CHTOI (unsigned int) ; 
 int HSU_CH_DCR_DESCA (unsigned int) ; 
 int /*<<< orphan*/  HSU_CH_DxSAR (unsigned int) ; 
 int /*<<< orphan*/  HSU_CH_DxTSR (unsigned int) ; 
 int /*<<< orphan*/  HSU_CH_MTSR ; 
 unsigned int HSU_DMA_CHAN_NR_DESC ; 
 int /*<<< orphan*/  hsu_chan_disable (struct hsu_dma_chan*) ; 
 int /*<<< orphan*/  hsu_chan_enable (struct hsu_dma_chan*) ; 
 int /*<<< orphan*/  hsu_chan_writel (struct hsu_dma_chan*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hsu_dma_chan_start(struct hsu_dma_chan *hsuc)
{
	struct dma_slave_config *config = &hsuc->config;
	struct hsu_dma_desc *desc = hsuc->desc;
	u32 bsr = 0, mtsr = 0;	/* to shut the compiler up */
	u32 dcr = HSU_CH_DCR_CHSOE | HSU_CH_DCR_CHEI;
	unsigned int i, count;

	if (hsuc->direction == DMA_MEM_TO_DEV) {
		bsr = config->dst_maxburst;
		mtsr = config->dst_addr_width;
	} else if (hsuc->direction == DMA_DEV_TO_MEM) {
		bsr = config->src_maxburst;
		mtsr = config->src_addr_width;
	}

	hsu_chan_disable(hsuc);

	hsu_chan_writel(hsuc, HSU_CH_DCR, 0);
	hsu_chan_writel(hsuc, HSU_CH_BSR, bsr);
	hsu_chan_writel(hsuc, HSU_CH_MTSR, mtsr);

	/* Set descriptors */
	count = desc->nents - desc->active;
	for (i = 0; i < count && i < HSU_DMA_CHAN_NR_DESC; i++) {
		hsu_chan_writel(hsuc, HSU_CH_DxSAR(i), desc->sg[i].addr);
		hsu_chan_writel(hsuc, HSU_CH_DxTSR(i), desc->sg[i].len);

		/* Prepare value for DCR */
		dcr |= HSU_CH_DCR_DESCA(i);
		dcr |= HSU_CH_DCR_CHTOI(i);	/* timeout bit, see HSU Errata 1 */

		desc->active++;
	}
	/* Only for the last descriptor in the chain */
	dcr |= HSU_CH_DCR_CHSOD(count - 1);
	dcr |= HSU_CH_DCR_CHDI(count - 1);

	hsu_chan_writel(hsuc, HSU_CH_DCR, dcr);

	hsu_chan_enable(hsuc);
}