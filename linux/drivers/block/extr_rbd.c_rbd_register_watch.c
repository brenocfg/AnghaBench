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
struct rbd_device {scalar_t__ watch_state; int /*<<< orphan*/  watch_mutex; TYPE_1__* watch_handle; int /*<<< orphan*/  watch_cookie; } ;
struct TYPE_2__ {int /*<<< orphan*/  linger_id; } ;

/* Variables and functions */
 scalar_t__ RBD_WATCH_STATE_REGISTERED ; 
 scalar_t__ RBD_WATCH_STATE_UNREGISTERED ; 
 int __rbd_register_watch (struct rbd_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbd_assert (int) ; 

__attribute__((used)) static int rbd_register_watch(struct rbd_device *rbd_dev)
{
	int ret;

	mutex_lock(&rbd_dev->watch_mutex);
	rbd_assert(rbd_dev->watch_state == RBD_WATCH_STATE_UNREGISTERED);
	ret = __rbd_register_watch(rbd_dev);
	if (ret)
		goto out;

	rbd_dev->watch_state = RBD_WATCH_STATE_REGISTERED;
	rbd_dev->watch_cookie = rbd_dev->watch_handle->linger_id;

out:
	mutex_unlock(&rbd_dev->watch_mutex);
	return ret;
}