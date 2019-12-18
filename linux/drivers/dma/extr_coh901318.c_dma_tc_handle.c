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
struct coh901318_chan {int /*<<< orphan*/  tasklet; int /*<<< orphan*/  lock; scalar_t__ busy; int /*<<< orphan*/  nbr_active_done; int /*<<< orphan*/  active; int /*<<< orphan*/  allocated; } ;
struct TYPE_2__ {scalar_t__ priority_high; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COHC_2_DEV (struct coh901318_chan*) ; 
 int /*<<< orphan*/ * coh901318_queue_start (struct coh901318_chan*) ; 
 TYPE_1__* cohc_chan_conf (struct coh901318_chan*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dma_tc_handle(struct coh901318_chan *cohc)
{
	/*
	 * If the channel is not allocated, then we shouldn't have
	 * any TC interrupts on it.
	 */
	if (!cohc->allocated) {
		dev_err(COHC_2_DEV(cohc), "spurious interrupt from "
			"unallocated channel\n");
		return;
	}

	spin_lock(&cohc->lock);

	/*
	 * When we reach this point, at least one queue item
	 * should have been moved over from cohc->queue to
	 * cohc->active and run to completion, that is why we're
	 * getting a terminal count interrupt is it not?
	 * If you get this BUG() the most probable cause is that
	 * the individual nodes in the lli chain have IRQ enabled,
	 * so check your platform config for lli chain ctrl.
	 */
	BUG_ON(list_empty(&cohc->active));

	cohc->nbr_active_done++;

	/*
	 * This attempt to take a job from cohc->queue, put it
	 * into cohc->active and start it.
	 */
	if (coh901318_queue_start(cohc) == NULL)
		cohc->busy = 0;

	spin_unlock(&cohc->lock);

	/*
	 * This tasklet will remove items from cohc->active
	 * and thus terminates them.
	 */
	if (cohc_chan_conf(cohc)->priority_high)
		tasklet_hi_schedule(&cohc->tasklet);
	else
		tasklet_schedule(&cohc->tasklet);
}