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
struct mtk_cqdma_device {size_t dma_channels; TYPE_1__** pc; int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cqdma2dev (struct mtk_cqdma_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mtk_cqdma_hard_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mtk_cqdma_hw_init(struct mtk_cqdma_device *cqdma)
{
	unsigned long flags;
	int err;
	u32 i;

	pm_runtime_enable(cqdma2dev(cqdma));
	pm_runtime_get_sync(cqdma2dev(cqdma));

	err = clk_prepare_enable(cqdma->clk);

	if (err) {
		pm_runtime_put_sync(cqdma2dev(cqdma));
		pm_runtime_disable(cqdma2dev(cqdma));
		return err;
	}

	/* reset all PCs */
	for (i = 0; i < cqdma->dma_channels; ++i) {
		spin_lock_irqsave(&cqdma->pc[i]->lock, flags);
		if (mtk_cqdma_hard_reset(cqdma->pc[i]) < 0) {
			dev_err(cqdma2dev(cqdma), "cqdma hard reset timeout\n");
			spin_unlock_irqrestore(&cqdma->pc[i]->lock, flags);

			clk_disable_unprepare(cqdma->clk);
			pm_runtime_put_sync(cqdma2dev(cqdma));
			pm_runtime_disable(cqdma2dev(cqdma));
			return -EINVAL;
		}
		spin_unlock_irqrestore(&cqdma->pc[i]->lock, flags);
	}

	return 0;
}