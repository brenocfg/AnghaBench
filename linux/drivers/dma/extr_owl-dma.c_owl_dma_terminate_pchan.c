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
struct owl_dma_pchan {int id; int /*<<< orphan*/ * vchan; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct owl_dma {int /*<<< orphan*/  lock; TYPE_1__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  OWL_DMAX_INT_STATUS ; 
 int /*<<< orphan*/  OWL_DMAX_START ; 
 int /*<<< orphan*/  OWL_DMA_IRQ_EN0 ; 
 int /*<<< orphan*/  OWL_DMA_IRQ_PD0 ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int dma_readl (struct owl_dma*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_update (struct owl_dma*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dma_writel (struct owl_dma*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pchan_update (struct owl_dma_pchan*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pchan_writel (struct owl_dma_pchan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void owl_dma_terminate_pchan(struct owl_dma *od,
				    struct owl_dma_pchan *pchan)
{
	unsigned long flags;
	u32 irq_pd;

	pchan_writel(pchan, OWL_DMAX_START, 0);
	pchan_update(pchan, OWL_DMAX_INT_STATUS, 0xff, false);

	spin_lock_irqsave(&od->lock, flags);
	dma_update(od, OWL_DMA_IRQ_EN0, (1 << pchan->id), false);

	irq_pd = dma_readl(od, OWL_DMA_IRQ_PD0);
	if (irq_pd & (1 << pchan->id)) {
		dev_warn(od->dma.dev,
			 "terminating pchan %d that still has pending irq\n",
			 pchan->id);
		dma_writel(od, OWL_DMA_IRQ_PD0, (1 << pchan->id));
	}

	pchan->vchan = NULL;

	spin_unlock_irqrestore(&od->lock, flags);
}