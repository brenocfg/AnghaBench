#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* device; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; TYPE_2__ chan; } ;
struct mtk_chan {scalar_t__ dir; TYPE_3__ vc; int /*<<< orphan*/  irq; scalar_t__ base; } ;
struct dma_chan {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFF_DEBUG_STATUS ; 
 scalar_t__ VFF_EN ; 
 scalar_t__ VFF_FLUSH ; 
 unsigned int VFF_FLUSH_B ; 
 scalar_t__ VFF_INT_EN ; 
 unsigned int VFF_INT_EN_CLR_B ; 
 scalar_t__ VFF_INT_FLAG ; 
 unsigned int VFF_RX_INT_CLR_B ; 
 scalar_t__ VFF_STOP ; 
 unsigned int VFF_STOP_B ; 
 unsigned int VFF_STOP_CLR_B ; 
 unsigned int VFF_TX_INT_CLR_B ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  mtk_uart_apdma_read (struct mtk_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_uart_apdma_write (struct mtk_chan*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  readl ; 
 int readx_poll_timeout (int /*<<< orphan*/ ,scalar_t__,unsigned int,int,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 struct mtk_chan* to_mtk_uart_apdma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtk_uart_apdma_terminate_all(struct dma_chan *chan)
{
	struct mtk_chan *c = to_mtk_uart_apdma_chan(chan);
	unsigned long flags;
	unsigned int status;
	LIST_HEAD(head);
	int ret;

	mtk_uart_apdma_write(c, VFF_FLUSH, VFF_FLUSH_B);

	ret = readx_poll_timeout(readl, c->base + VFF_FLUSH,
			  status, status != VFF_FLUSH_B, 10, 100);
	if (ret)
		dev_err(c->vc.chan.device->dev, "flush: fail, status=0x%x\n",
			mtk_uart_apdma_read(c, VFF_DEBUG_STATUS));

	/*
	 * Stop need 3 steps.
	 * 1. set stop to 1
	 * 2. wait en to 0
	 * 3. set stop as 0
	 */
	mtk_uart_apdma_write(c, VFF_STOP, VFF_STOP_B);
	ret = readx_poll_timeout(readl, c->base + VFF_EN,
			  status, !status, 10, 100);
	if (ret)
		dev_err(c->vc.chan.device->dev, "stop: fail, status=0x%x\n",
			mtk_uart_apdma_read(c, VFF_DEBUG_STATUS));

	mtk_uart_apdma_write(c, VFF_STOP, VFF_STOP_CLR_B);
	mtk_uart_apdma_write(c, VFF_INT_EN, VFF_INT_EN_CLR_B);

	if (c->dir == DMA_DEV_TO_MEM)
		mtk_uart_apdma_write(c, VFF_INT_FLAG, VFF_RX_INT_CLR_B);
	else if (c->dir == DMA_MEM_TO_DEV)
		mtk_uart_apdma_write(c, VFF_INT_FLAG, VFF_TX_INT_CLR_B);

	synchronize_irq(c->irq);

	spin_lock_irqsave(&c->vc.lock, flags);
	vchan_get_all_descriptors(&c->vc, &head);
	vchan_dma_desc_free_list(&c->vc, &head);
	spin_unlock_irqrestore(&c->vc.lock, flags);

	return 0;
}