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
struct rbd_device {int /*<<< orphan*/  lock_dwork; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rbd_release_lock (struct rbd_device*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbd_quiesce_lock (struct rbd_device*) ; 

__attribute__((used)) static void rbd_release_lock(struct rbd_device *rbd_dev)
{
	if (!rbd_quiesce_lock(rbd_dev))
		return;

	__rbd_release_lock(rbd_dev);

	/*
	 * Give others a chance to grab the lock - we would re-acquire
	 * almost immediately if we got new IO while draining the running
	 * list otherwise.  We need to ack our own notifications, so this
	 * lock_dwork will be requeued from rbd_handle_released_lock() by
	 * way of maybe_kick_acquire().
	 */
	cancel_delayed_work(&rbd_dev->lock_dwork);
}