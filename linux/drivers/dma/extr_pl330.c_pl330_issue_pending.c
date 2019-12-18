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
struct dma_pl330_chan {int active; int /*<<< orphan*/  lock; int /*<<< orphan*/  work_list; int /*<<< orphan*/  submitted_list; TYPE_2__* dmac; } ;
struct dma_chan {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ ddma; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pl330_tasklet (unsigned long) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct dma_pl330_chan* to_pchan (struct dma_chan*) ; 

__attribute__((used)) static void pl330_issue_pending(struct dma_chan *chan)
{
	struct dma_pl330_chan *pch = to_pchan(chan);
	unsigned long flags;

	spin_lock_irqsave(&pch->lock, flags);
	if (list_empty(&pch->work_list)) {
		/*
		 * Warn on nothing pending. Empty submitted_list may
		 * break our pm_runtime usage counter as it is
		 * updated on work_list emptiness status.
		 */
		WARN_ON(list_empty(&pch->submitted_list));
		pch->active = true;
		pm_runtime_get_sync(pch->dmac->ddma.dev);
	}
	list_splice_tail_init(&pch->submitted_list, &pch->work_list);
	spin_unlock_irqrestore(&pch->lock, flags);

	pl330_tasklet((unsigned long)pch);
}