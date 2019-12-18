#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct mtk_uart_apdmadev {TYPE_1__ ddev; } ;
struct TYPE_4__ {int /*<<< orphan*/  task; } ;
struct mtk_chan {TYPE_2__ vc; int /*<<< orphan*/  irq; } ;
struct dma_chan {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct dma_chan*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 struct mtk_chan* to_mtk_uart_apdma_chan (struct dma_chan*) ; 
 struct mtk_uart_apdmadev* to_mtk_uart_apdma_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchan_free_chan_resources (TYPE_2__*) ; 

__attribute__((used)) static void mtk_uart_apdma_free_chan_resources(struct dma_chan *chan)
{
	struct mtk_uart_apdmadev *mtkd = to_mtk_uart_apdma_dev(chan->device);
	struct mtk_chan *c = to_mtk_uart_apdma_chan(chan);

	free_irq(c->irq, chan);

	tasklet_kill(&c->vc.task);

	vchan_free_chan_resources(&c->vc);

	pm_runtime_put_sync(mtkd->ddev.dev);
}