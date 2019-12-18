#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  device_node; } ;
struct TYPE_6__ {int /*<<< orphan*/  task; TYPE_1__ chan; } ;
struct mtk_cqdma_vchan {TYPE_2__ vc; } ;
struct mtk_cqdma_device {int dma_requests; int dma_channels; int /*<<< orphan*/  ddev; TYPE_4__** pc; struct mtk_cqdma_vchan* vc; } ;
struct TYPE_8__ {int /*<<< orphan*/  tasklet; int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_CQDMA_INT_EN ; 
 int /*<<< orphan*/  MTK_CQDMA_INT_EN_BIT ; 
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_cqdma_hw_deinit (struct mtk_cqdma_device*) ; 
 int /*<<< orphan*/  mtk_dma_clr (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_dma_controller_free (int /*<<< orphan*/ ) ; 
 struct mtk_cqdma_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtk_cqdma_remove(struct platform_device *pdev)
{
	struct mtk_cqdma_device *cqdma = platform_get_drvdata(pdev);
	struct mtk_cqdma_vchan *vc;
	unsigned long flags;
	int i;

	/* kill VC task */
	for (i = 0; i < cqdma->dma_requests; i++) {
		vc = &cqdma->vc[i];

		list_del(&vc->vc.chan.device_node);
		tasklet_kill(&vc->vc.task);
	}

	/* disable interrupt */
	for (i = 0; i < cqdma->dma_channels; i++) {
		spin_lock_irqsave(&cqdma->pc[i]->lock, flags);
		mtk_dma_clr(cqdma->pc[i], MTK_CQDMA_INT_EN,
			    MTK_CQDMA_INT_EN_BIT);
		spin_unlock_irqrestore(&cqdma->pc[i]->lock, flags);

		/* Waits for any pending IRQ handlers to complete */
		synchronize_irq(cqdma->pc[i]->irq);

		tasklet_kill(&cqdma->pc[i]->tasklet);
	}

	/* disable hardware */
	mtk_cqdma_hw_deinit(cqdma);

	dma_async_device_unregister(&cqdma->ddev);
	of_dma_controller_free(pdev->dev.of_node);

	return 0;
}