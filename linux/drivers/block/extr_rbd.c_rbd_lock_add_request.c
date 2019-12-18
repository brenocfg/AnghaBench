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
struct rbd_img_request {int /*<<< orphan*/  lock_item; struct rbd_device* rbd_dev; } ;
struct rbd_device {scalar_t__ lock_state; int /*<<< orphan*/  lock_lists_lock; int /*<<< orphan*/  running_list; int /*<<< orphan*/  acquiring_list; int /*<<< orphan*/  lock_rwsem; } ;

/* Variables and functions */
 scalar_t__ RBD_LOCK_STATE_LOCKED ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbd_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool rbd_lock_add_request(struct rbd_img_request *img_req)
{
	struct rbd_device *rbd_dev = img_req->rbd_dev;
	bool locked;

	lockdep_assert_held(&rbd_dev->lock_rwsem);
	locked = rbd_dev->lock_state == RBD_LOCK_STATE_LOCKED;
	spin_lock(&rbd_dev->lock_lists_lock);
	rbd_assert(list_empty(&img_req->lock_item));
	if (!locked)
		list_add_tail(&img_req->lock_item, &rbd_dev->acquiring_list);
	else
		list_add_tail(&img_req->lock_item, &rbd_dev->running_list);
	spin_unlock(&rbd_dev->lock_lists_lock);
	return locked;
}