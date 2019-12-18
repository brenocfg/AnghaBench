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
typedef  size_t u32 ;
struct dw_axi_dma {struct axi_dma_chan* chan; TYPE_1__* hdata; } ;
struct axi_dma_chip {int /*<<< orphan*/  dev; struct dw_axi_dma* dw; } ;
struct axi_dma_chan {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {size_t nr_channels; } ;

/* Variables and functions */
 size_t DWAXIDMAC_IRQ_ALL_ERR ; 
 size_t DWAXIDMAC_IRQ_DMA_TRF ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  axi_chan_block_xfer_complete (struct axi_dma_chan*) ; 
 int /*<<< orphan*/  axi_chan_handle_err (struct axi_dma_chan*,size_t) ; 
 int /*<<< orphan*/  axi_chan_irq_clear (struct axi_dma_chan*,size_t) ; 
 size_t axi_chan_irq_read (struct axi_dma_chan*) ; 
 int /*<<< orphan*/  axi_chan_name (struct axi_dma_chan*) ; 
 int /*<<< orphan*/  axi_dma_irq_disable (struct axi_dma_chip*) ; 
 int /*<<< orphan*/  axi_dma_irq_enable (struct axi_dma_chip*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,size_t) ; 

__attribute__((used)) static irqreturn_t dw_axi_dma_interrupt(int irq, void *dev_id)
{
	struct axi_dma_chip *chip = dev_id;
	struct dw_axi_dma *dw = chip->dw;
	struct axi_dma_chan *chan;

	u32 status, i;

	/* Disable DMAC inerrupts. We'll enable them after processing chanels */
	axi_dma_irq_disable(chip);

	/* Poll, clear and process every chanel interrupt status */
	for (i = 0; i < dw->hdata->nr_channels; i++) {
		chan = &dw->chan[i];
		status = axi_chan_irq_read(chan);
		axi_chan_irq_clear(chan, status);

		dev_vdbg(chip->dev, "%s %u IRQ status: 0x%08x\n",
			axi_chan_name(chan), i, status);

		if (status & DWAXIDMAC_IRQ_ALL_ERR)
			axi_chan_handle_err(chan, status);
		else if (status & DWAXIDMAC_IRQ_DMA_TRF)
			axi_chan_block_xfer_complete(chan);
	}

	/* Re-enable interrupts */
	axi_dma_irq_enable(chip);

	return IRQ_HANDLED;
}