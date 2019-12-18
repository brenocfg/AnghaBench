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
struct dma_channel {int flags; int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 scalar_t__ CHCR ; 
 int CHCR_DE ; 
 int CHCR_IE ; 
 int CHCR_TE ; 
 int DMA_TEI_CAPABLE ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  disable_irq (int) ; 
 scalar_t__ dma_base_addr (int /*<<< orphan*/ ) ; 
 int get_dmte_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_dmac_disable_dma(struct dma_channel *chan)
{
	int irq;
	u32 chcr;

	if (chan->flags & DMA_TEI_CAPABLE) {
		irq = get_dmte_irq(chan->chan);
		disable_irq(irq);
	}

	chcr = __raw_readl(dma_base_addr(chan->chan) + CHCR);
	chcr &= ~(CHCR_DE | CHCR_TE | CHCR_IE);
	__raw_writel(chcr, (dma_base_addr(chan->chan) + CHCR));
}