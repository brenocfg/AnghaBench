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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct mtk_chan {scalar_t__ dir; TYPE_1__ vc; } ;
struct dma_chan {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  mtk_uart_apdma_rx_handler (struct mtk_chan*) ; 
 int /*<<< orphan*/  mtk_uart_apdma_tx_handler (struct mtk_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mtk_chan* to_mtk_uart_apdma_chan (struct dma_chan*) ; 

__attribute__((used)) static irqreturn_t mtk_uart_apdma_irq_handler(int irq, void *dev_id)
{
	struct dma_chan *chan = (struct dma_chan *)dev_id;
	struct mtk_chan *c = to_mtk_uart_apdma_chan(chan);
	unsigned long flags;

	spin_lock_irqsave(&c->vc.lock, flags);
	if (c->dir == DMA_DEV_TO_MEM)
		mtk_uart_apdma_rx_handler(c);
	else if (c->dir == DMA_MEM_TO_DEV)
		mtk_uart_apdma_tx_handler(c);
	spin_unlock_irqrestore(&c->vc.lock, flags);

	return IRQ_HANDLED;
}