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
struct request_queue {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  rpm_status; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPM_ACTIVE ; 
 int /*<<< orphan*/  RPM_SUSPENDED ; 
 int /*<<< orphan*/  blk_clear_pm_only (struct request_queue*) ; 
 int /*<<< orphan*/  pm_request_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void blk_post_runtime_resume(struct request_queue *q, int err)
{
	if (!q->dev)
		return;

	spin_lock_irq(&q->queue_lock);
	if (!err) {
		q->rpm_status = RPM_ACTIVE;
		pm_runtime_mark_last_busy(q->dev);
		pm_request_autosuspend(q->dev);
	} else {
		q->rpm_status = RPM_SUSPENDED;
	}
	spin_unlock_irq(&q->queue_lock);

	if (!err)
		blk_clear_pm_only(q);
}