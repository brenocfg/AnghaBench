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
struct xgene_dma_chan {int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  dev; struct xgene_dma_chan* chan; int /*<<< orphan*/  err_irq; } ;
struct xgene_dma {int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  dev; struct xgene_dma* chan; int /*<<< orphan*/  err_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_DISABLE_UNLAZY ; 
 int XGENE_DMA_MAX_CHANNEL ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xgene_dma_chan*) ; 
 int /*<<< orphan*/  irq_clear_status_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgene_dma_free_irqs(struct xgene_dma *pdma)
{
	struct xgene_dma_chan *chan;
	int i;

	/* Free DMA device error irq */
	devm_free_irq(pdma->dev, pdma->err_irq, pdma);

	for (i = 0; i < XGENE_DMA_MAX_CHANNEL; i++) {
		chan = &pdma->chan[i];
		irq_clear_status_flags(chan->rx_irq, IRQ_DISABLE_UNLAZY);
		devm_free_irq(chan->dev, chan->rx_irq, chan);
	}
}