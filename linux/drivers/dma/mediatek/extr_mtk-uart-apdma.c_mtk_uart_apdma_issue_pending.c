#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct virt_dma_desc {int /*<<< orphan*/  tx; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct mtk_chan {scalar_t__ dir; TYPE_1__ vc; int /*<<< orphan*/  desc; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 scalar_t__ DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  mtk_uart_apdma_start_rx (struct mtk_chan*) ; 
 int /*<<< orphan*/  mtk_uart_apdma_start_tx (struct mtk_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mtk_chan* to_mtk_uart_apdma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  to_mtk_uart_apdma_desc (int /*<<< orphan*/ *) ; 
 scalar_t__ vchan_issue_pending (TYPE_1__*) ; 
 struct virt_dma_desc* vchan_next_desc (TYPE_1__*) ; 

__attribute__((used)) static void mtk_uart_apdma_issue_pending(struct dma_chan *chan)
{
	struct mtk_chan *c = to_mtk_uart_apdma_chan(chan);
	struct virt_dma_desc *vd;
	unsigned long flags;

	spin_lock_irqsave(&c->vc.lock, flags);
	if (vchan_issue_pending(&c->vc)) {
		vd = vchan_next_desc(&c->vc);
		c->desc = to_mtk_uart_apdma_desc(&vd->tx);

		if (c->dir == DMA_DEV_TO_MEM)
			mtk_uart_apdma_start_rx(c);
		else if (c->dir == DMA_MEM_TO_DEV)
			mtk_uart_apdma_start_tx(c);
	}

	spin_unlock_irqrestore(&c->vc.lock, flags);
}