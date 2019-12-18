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
struct stm32_dma_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct stm32_dma_chan {TYPE_1__ vchan; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int STM32_DMA_FEI ; 
 int STM32_DMA_HTI ; 
 int /*<<< orphan*/  STM32_DMA_SCR (int /*<<< orphan*/ ) ; 
 int STM32_DMA_SCR_EN ; 
 int STM32_DMA_SCR_TCIE ; 
 int /*<<< orphan*/  STM32_DMA_SFCR (int /*<<< orphan*/ ) ; 
 int STM32_DMA_SFCR_FEIE ; 
 int STM32_DMA_TCI ; 
 int /*<<< orphan*/  chan2dev (struct stm32_dma_chan*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct stm32_dma_device* stm32_dma_get_dev (struct stm32_dma_chan*) ; 
 int /*<<< orphan*/  stm32_dma_handle_chan_done (struct stm32_dma_chan*) ; 
 int /*<<< orphan*/  stm32_dma_irq_clear (struct stm32_dma_chan*,int) ; 
 int stm32_dma_irq_status (struct stm32_dma_chan*) ; 
 int stm32_dma_read (struct stm32_dma_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t stm32_dma_chan_irq(int irq, void *devid)
{
	struct stm32_dma_chan *chan = devid;
	struct stm32_dma_device *dmadev = stm32_dma_get_dev(chan);
	u32 status, scr, sfcr;

	spin_lock(&chan->vchan.lock);

	status = stm32_dma_irq_status(chan);
	scr = stm32_dma_read(dmadev, STM32_DMA_SCR(chan->id));
	sfcr = stm32_dma_read(dmadev, STM32_DMA_SFCR(chan->id));

	if (status & STM32_DMA_TCI) {
		stm32_dma_irq_clear(chan, STM32_DMA_TCI);
		if (scr & STM32_DMA_SCR_TCIE)
			stm32_dma_handle_chan_done(chan);
		status &= ~STM32_DMA_TCI;
	}
	if (status & STM32_DMA_HTI) {
		stm32_dma_irq_clear(chan, STM32_DMA_HTI);
		status &= ~STM32_DMA_HTI;
	}
	if (status & STM32_DMA_FEI) {
		stm32_dma_irq_clear(chan, STM32_DMA_FEI);
		status &= ~STM32_DMA_FEI;
		if (sfcr & STM32_DMA_SFCR_FEIE) {
			if (!(scr & STM32_DMA_SCR_EN))
				dev_err(chan2dev(chan), "FIFO Error\n");
			else
				dev_dbg(chan2dev(chan), "FIFO over/underrun\n");
		}
	}
	if (status) {
		stm32_dma_irq_clear(chan, status);
		dev_err(chan2dev(chan), "DMA error: status=0x%08x\n", status);
		if (!(scr & STM32_DMA_SCR_EN))
			dev_err(chan2dev(chan), "chan disabled by HW\n");
	}

	spin_unlock(&chan->vchan.lock);

	return IRQ_HANDLED;
}