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
struct TYPE_2__ {int /*<<< orphan*/  tx; } ;
struct mtk_cqdma_vdesc {struct mtk_cqdma_vdesc* parent; TYPE_1__ vd; } ;
struct mtk_cqdma_pchan {int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_run_dependencies (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mtk_cqdma_vdesc*) ; 
 struct mtk_cqdma_vdesc* mtk_cqdma_consume_work_queue (struct mtk_cqdma_pchan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mtk_cqdma_tasklet_cb(unsigned long data)
{
	struct mtk_cqdma_pchan *pc = (struct mtk_cqdma_pchan *)data;
	struct mtk_cqdma_vdesc *cvd = NULL;
	unsigned long flags;

	spin_lock_irqsave(&pc->lock, flags);
	/* consume the queue */
	cvd = mtk_cqdma_consume_work_queue(pc);
	spin_unlock_irqrestore(&pc->lock, flags);

	/* submit the next CVD */
	if (cvd) {
		dma_run_dependencies(&cvd->vd.tx);

		/*
		 * free child CVD after completion.
		 * the parent CVD would be freeed with desc_free by user.
		 */
		if (cvd->parent != cvd)
			kfree(cvd);
	}

	/* re-enable interrupt before leaving tasklet */
	enable_irq(pc->irq);
}