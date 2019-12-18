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
typedef  size_t u32 ;
struct mtk_cqdma_device {size_t dma_channels; TYPE_1__** pc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  tasklet; int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  MTK_CQDMA_INT_FLAG ; 
 int MTK_CQDMA_INT_FLAG_BIT ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_dma_clr (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int mtk_dma_read (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mtk_cqdma_irq(int irq, void *devid)
{
	struct mtk_cqdma_device *cqdma = devid;
	irqreturn_t ret = IRQ_NONE;
	bool schedule_tasklet = false;
	u32 i;

	/* clear interrupt flags for each PC */
	for (i = 0; i < cqdma->dma_channels; ++i, schedule_tasklet = false) {
		spin_lock(&cqdma->pc[i]->lock);
		if (mtk_dma_read(cqdma->pc[i],
				 MTK_CQDMA_INT_FLAG) & MTK_CQDMA_INT_FLAG_BIT) {
			/* clear interrupt */
			mtk_dma_clr(cqdma->pc[i], MTK_CQDMA_INT_FLAG,
				    MTK_CQDMA_INT_FLAG_BIT);

			schedule_tasklet = true;
			ret = IRQ_HANDLED;
		}
		spin_unlock(&cqdma->pc[i]->lock);

		if (schedule_tasklet) {
			/* disable interrupt */
			disable_irq_nosync(cqdma->pc[i]->irq);

			/* schedule the tasklet to handle the transactions */
			tasklet_schedule(&cqdma->pc[i]->tasklet);
		}
	}

	return ret;
}