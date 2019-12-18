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
struct mtk_chan {TYPE_1__ vc; int /*<<< orphan*/  irq; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFF_EN ; 
 int /*<<< orphan*/  VFF_EN_CLR_B ; 
 int /*<<< orphan*/  VFF_INT_EN ; 
 int /*<<< orphan*/  VFF_INT_EN_CLR_B ; 
 int /*<<< orphan*/  mtk_uart_apdma_write (struct mtk_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 struct mtk_chan* to_mtk_uart_apdma_chan (struct dma_chan*) ; 

__attribute__((used)) static int mtk_uart_apdma_device_pause(struct dma_chan *chan)
{
	struct mtk_chan *c = to_mtk_uart_apdma_chan(chan);
	unsigned long flags;

	spin_lock_irqsave(&c->vc.lock, flags);

	mtk_uart_apdma_write(c, VFF_EN, VFF_EN_CLR_B);
	mtk_uart_apdma_write(c, VFF_INT_EN, VFF_INT_EN_CLR_B);

	synchronize_irq(c->irq);

	spin_unlock_irqrestore(&c->vc.lock, flags);

	return 0;
}