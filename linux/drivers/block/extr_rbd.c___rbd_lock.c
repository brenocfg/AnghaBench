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
struct rbd_device {int /*<<< orphan*/  acquired_lock_work; int /*<<< orphan*/  task_wq; int /*<<< orphan*/  lock_cookie; int /*<<< orphan*/  lock_state; } ;
struct rbd_client_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RBD_LOCK_STATE_LOCKED ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct rbd_client_id rbd_get_cid (struct rbd_device*) ; 
 int /*<<< orphan*/  rbd_set_owner_cid (struct rbd_device*,struct rbd_client_id*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void __rbd_lock(struct rbd_device *rbd_dev, const char *cookie)
{
	struct rbd_client_id cid = rbd_get_cid(rbd_dev);

	rbd_dev->lock_state = RBD_LOCK_STATE_LOCKED;
	strcpy(rbd_dev->lock_cookie, cookie);
	rbd_set_owner_cid(rbd_dev, &cid);
	queue_work(rbd_dev->task_wq, &rbd_dev->acquired_lock_work);
}