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
struct request_queue {int /*<<< orphan*/  queue_lock; scalar_t__ dev; int /*<<< orphan*/  rpm_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPM_ACTIVE ; 
 int /*<<< orphan*/  pm_request_autosuspend (scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void blk_set_runtime_active(struct request_queue *q)
{
	if (q->dev) {
		spin_lock_irq(&q->queue_lock);
		q->rpm_status = RPM_ACTIVE;
		pm_runtime_mark_last_busy(q->dev);
		pm_request_autosuspend(q->dev);
		spin_unlock_irq(&q->queue_lock);
	}
}