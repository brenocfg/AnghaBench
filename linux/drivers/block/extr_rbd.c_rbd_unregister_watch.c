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
struct rbd_device {scalar_t__ watch_state; TYPE_2__* rbd_client; int /*<<< orphan*/  watch_dwork; int /*<<< orphan*/  watch_mutex; } ;
struct TYPE_4__ {TYPE_1__* client; } ;
struct TYPE_3__ {int /*<<< orphan*/  osdc; } ;

/* Variables and functions */
 scalar_t__ RBD_WATCH_STATE_REGISTERED ; 
 scalar_t__ RBD_WATCH_STATE_UNREGISTERED ; 
 int /*<<< orphan*/  __rbd_unregister_watch (struct rbd_device*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_tasks_sync (struct rbd_device*) ; 
 int /*<<< orphan*/  ceph_osdc_flush_notifies (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rbd_unregister_watch(struct rbd_device *rbd_dev)
{
	cancel_tasks_sync(rbd_dev);

	mutex_lock(&rbd_dev->watch_mutex);
	if (rbd_dev->watch_state == RBD_WATCH_STATE_REGISTERED)
		__rbd_unregister_watch(rbd_dev);
	rbd_dev->watch_state = RBD_WATCH_STATE_UNREGISTERED;
	mutex_unlock(&rbd_dev->watch_mutex);

	cancel_delayed_work_sync(&rbd_dev->watch_dwork);
	ceph_osdc_flush_notifies(&rbd_dev->rbd_client->client->osdc);
}