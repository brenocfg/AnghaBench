#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int features; } ;
struct rbd_device {long acquire_err; TYPE_3__* opts; int /*<<< orphan*/  lock_dwork; int /*<<< orphan*/  acquire_wait; int /*<<< orphan*/  task_wq; TYPE_2__* spec; TYPE_1__ header; } ;
struct TYPE_6__ {int /*<<< orphan*/  exclusive; int /*<<< orphan*/  lock_timeout; int /*<<< orphan*/  lock_on_read; } ;
struct TYPE_5__ {scalar_t__ snap_id; } ;

/* Variables and functions */
 scalar_t__ CEPH_NOSNAP ; 
 int EINVAL ; 
 long ETIMEDOUT ; 
 int RBD_FEATURE_EXCLUSIVE_LOCK ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_timeout_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbd_assert (int) ; 
 scalar_t__ rbd_is_lock_owner (struct rbd_device*) ; 
 int /*<<< orphan*/  rbd_warn (struct rbd_device*,char*,...) ; 
 long wait_for_completion_killable_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rbd_add_acquire_lock(struct rbd_device *rbd_dev)
{
	long ret;

	if (!(rbd_dev->header.features & RBD_FEATURE_EXCLUSIVE_LOCK)) {
		if (!rbd_dev->opts->exclusive && !rbd_dev->opts->lock_on_read)
			return 0;

		rbd_warn(rbd_dev, "exclusive-lock feature is not enabled");
		return -EINVAL;
	}

	if (rbd_dev->spec->snap_id != CEPH_NOSNAP)
		return 0;

	rbd_assert(!rbd_is_lock_owner(rbd_dev));
	queue_delayed_work(rbd_dev->task_wq, &rbd_dev->lock_dwork, 0);
	ret = wait_for_completion_killable_timeout(&rbd_dev->acquire_wait,
			    ceph_timeout_jiffies(rbd_dev->opts->lock_timeout));
	if (ret > 0) {
		ret = rbd_dev->acquire_err;
	} else {
		cancel_delayed_work_sync(&rbd_dev->lock_dwork);
		if (!ret)
			ret = -ETIMEDOUT;
	}

	if (ret) {
		rbd_warn(rbd_dev, "failed to acquire exclusive lock: %ld", ret);
		return ret;
	}

	/*
	 * The lock may have been released by now, unless automatic lock
	 * transitions are disabled.
	 */
	rbd_assert(!rbd_dev->opts->exclusive || rbd_is_lock_owner(rbd_dev));
	return 0;
}