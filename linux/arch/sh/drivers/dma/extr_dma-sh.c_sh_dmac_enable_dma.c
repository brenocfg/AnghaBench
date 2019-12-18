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
typedef  int /*<<< orphan*/  u32 ;
struct dma_channel {int flags; int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 scalar_t__ CHCR ; 
 int /*<<< orphan*/  CHCR_DE ; 
 int /*<<< orphan*/  CHCR_IE ; 
 int DMA_TEI_CAPABLE ; 
 int /*<<< orphan*/  __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ dma_base_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int) ; 
 int get_dmte_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_dmac_enable_dma(struct dma_channel *chan)
{
	int irq;
	u32 chcr;

	chcr = __raw_readl(dma_base_addr(chan->chan) + CHCR);
	chcr |= CHCR_DE;

	if (chan->flags & DMA_TEI_CAPABLE)
		chcr |= CHCR_IE;

	__raw_writel(chcr, (dma_base_addr(chan->chan) + CHCR));

	if (chan->flags & DMA_TEI_CAPABLE) {
		irq = get_dmte_irq(chan->chan);
		enable_irq(irq);
	}
}