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
struct xgene_dma_chan {char* name; int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  dev; struct xgene_dma_chan* chan; int /*<<< orphan*/  err_irq; } ;
struct xgene_dma {char* name; int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  dev; struct xgene_dma* chan; int /*<<< orphan*/  err_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_DISABLE_UNLAZY ; 
 int XGENE_DMA_MAX_CHANNEL ; 
 int /*<<< orphan*/  chan_err (struct xgene_dma_chan*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xgene_dma_chan*) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct xgene_dma_chan*) ; 
 int /*<<< orphan*/  irq_clear_status_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_status_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_dma_chan_ring_isr ; 
 int /*<<< orphan*/  xgene_dma_err_isr ; 

__attribute__((used)) static int xgene_dma_request_irqs(struct xgene_dma *pdma)
{
	struct xgene_dma_chan *chan;
	int ret, i, j;

	/* Register DMA error irq */
	ret = devm_request_irq(pdma->dev, pdma->err_irq, xgene_dma_err_isr,
			       0, "dma_error", pdma);
	if (ret) {
		dev_err(pdma->dev,
			"Failed to register error IRQ %d\n", pdma->err_irq);
		return ret;
	}

	/* Register DMA channel rx irq */
	for (i = 0; i < XGENE_DMA_MAX_CHANNEL; i++) {
		chan = &pdma->chan[i];
		irq_set_status_flags(chan->rx_irq, IRQ_DISABLE_UNLAZY);
		ret = devm_request_irq(chan->dev, chan->rx_irq,
				       xgene_dma_chan_ring_isr,
				       0, chan->name, chan);
		if (ret) {
			chan_err(chan, "Failed to register Rx IRQ %d\n",
				 chan->rx_irq);
			devm_free_irq(pdma->dev, pdma->err_irq, pdma);

			for (j = 0; j < i; j++) {
				chan = &pdma->chan[i];
				irq_clear_status_flags(chan->rx_irq, IRQ_DISABLE_UNLAZY);
				devm_free_irq(chan->dev, chan->rx_irq, chan);
			}

			return ret;
		}
	}

	return 0;
}