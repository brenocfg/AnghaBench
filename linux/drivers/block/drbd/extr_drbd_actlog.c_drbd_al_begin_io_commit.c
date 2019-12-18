#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct drbd_device {int /*<<< orphan*/  al_wait; TYPE_3__* act_log; int /*<<< orphan*/  al_lock; TYPE_1__* ldev; } ;
struct TYPE_8__ {scalar_t__ pending_changes; } ;
struct TYPE_7__ {int al_updates; } ;
struct TYPE_6__ {int /*<<< orphan*/  disk_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  al_write_transaction (struct drbd_device*) ; 
 int /*<<< orphan*/  lc_committed (TYPE_3__*) ; 
 int lc_try_lock_for_transaction (TYPE_3__*) ; 
 int /*<<< orphan*/  lc_unlock (TYPE_3__*) ; 
 TYPE_2__* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void drbd_al_begin_io_commit(struct drbd_device *device)
{
	bool locked = false;

	/* Serialize multiple transactions.
	 * This uses test_and_set_bit, memory barrier is implicit.
	 */
	wait_event(device->al_wait,
			device->act_log->pending_changes == 0 ||
			(locked = lc_try_lock_for_transaction(device->act_log)));

	if (locked) {
		/* Double check: it may have been committed by someone else,
		 * while we have been waiting for the lock. */
		if (device->act_log->pending_changes) {
			bool write_al_updates;

			rcu_read_lock();
			write_al_updates = rcu_dereference(device->ldev->disk_conf)->al_updates;
			rcu_read_unlock();

			if (write_al_updates)
				al_write_transaction(device);
			spin_lock_irq(&device->al_lock);
			/* FIXME
			if (err)
				we need an "lc_cancel" here;
			*/
			lc_committed(device->act_log);
			spin_unlock_irq(&device->al_lock);
		}
		lc_unlock(device->act_log);
		wake_up(&device->al_wait);
	}
}