#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct request_queue {scalar_t__ rpm_status; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  q_usage_counter; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ RPM_ACTIVE ; 
 scalar_t__ RPM_SUSPENDING ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  blk_clear_pm_only (struct request_queue*) ; 
 int /*<<< orphan*/  blk_freeze_queue_start (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_unfreeze_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_set_pm_only (struct request_queue*) ; 
 scalar_t__ percpu_ref_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_switch_to_atomic_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int blk_pre_runtime_suspend(struct request_queue *q)
{
	int ret = 0;

	if (!q->dev)
		return ret;

	WARN_ON_ONCE(q->rpm_status != RPM_ACTIVE);

	/*
	 * Increase the pm_only counter before checking whether any
	 * non-PM blk_queue_enter() calls are in progress to avoid that any
	 * new non-PM blk_queue_enter() calls succeed before the pm_only
	 * counter is decreased again.
	 */
	blk_set_pm_only(q);
	ret = -EBUSY;
	/* Switch q_usage_counter from per-cpu to atomic mode. */
	blk_freeze_queue_start(q);
	/*
	 * Wait until atomic mode has been reached. Since that
	 * involves calling call_rcu(), it is guaranteed that later
	 * blk_queue_enter() calls see the pm-only state. See also
	 * http://lwn.net/Articles/573497/.
	 */
	percpu_ref_switch_to_atomic_sync(&q->q_usage_counter);
	if (percpu_ref_is_zero(&q->q_usage_counter))
		ret = 0;
	/* Switch q_usage_counter back to per-cpu mode. */
	blk_mq_unfreeze_queue(q);

	spin_lock_irq(&q->queue_lock);
	if (ret < 0)
		pm_runtime_mark_last_busy(q->dev);
	else
		q->rpm_status = RPM_SUSPENDING;
	spin_unlock_irq(&q->queue_lock);

	if (ret)
		blk_clear_pm_only(q);

	return ret;
}