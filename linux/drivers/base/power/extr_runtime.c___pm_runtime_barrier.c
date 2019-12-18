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
struct TYPE_2__ {int request_pending; scalar_t__ runtime_status; int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  lock; scalar_t__ idle_notification; int /*<<< orphan*/  work; int /*<<< orphan*/  request; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPM_REQ_NONE ; 
 scalar_t__ RPM_RESUMING ; 
 scalar_t__ RPM_SUSPENDING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_deactivate_timer (struct device*) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void __pm_runtime_barrier(struct device *dev)
{
	pm_runtime_deactivate_timer(dev);

	if (dev->power.request_pending) {
		dev->power.request = RPM_REQ_NONE;
		spin_unlock_irq(&dev->power.lock);

		cancel_work_sync(&dev->power.work);

		spin_lock_irq(&dev->power.lock);
		dev->power.request_pending = false;
	}

	if (dev->power.runtime_status == RPM_SUSPENDING
	    || dev->power.runtime_status == RPM_RESUMING
	    || dev->power.idle_notification) {
		DEFINE_WAIT(wait);

		/* Suspend, wake-up or idle notification in progress. */
		for (;;) {
			prepare_to_wait(&dev->power.wait_queue, &wait,
					TASK_UNINTERRUPTIBLE);
			if (dev->power.runtime_status != RPM_SUSPENDING
			    && dev->power.runtime_status != RPM_RESUMING
			    && !dev->power.idle_notification)
				break;
			spin_unlock_irq(&dev->power.lock);

			schedule();

			spin_lock_irq(&dev->power.lock);
		}
		finish_wait(&dev->power.wait_queue, &wait);
	}
}