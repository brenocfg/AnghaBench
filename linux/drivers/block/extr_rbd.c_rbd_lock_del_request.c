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
struct rbd_device {scalar_t__ lock_state; int /*<<< orphan*/  releasing_wait; int /*<<< orphan*/  lock_lists_lock; int /*<<< orphan*/  running_list; int /*<<< orphan*/  lock_rwsem; } ;

/* Variables and functions */
 scalar_t__ RBD_LOCK_STATE_RELEASING ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbd_assert (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rbd_lock_del_request(struct rbd_img_request *img_req)
{
	struct rbd_device *rbd_dev = img_req->rbd_dev;
	bool need_wakeup;

	lockdep_assert_held(&rbd_dev->lock_rwsem);
	spin_lock(&rbd_dev->lock_lists_lock);
	rbd_assert(!list_empty(&img_req->lock_item));
	list_del_init(&img_req->lock_item);
	need_wakeup = (rbd_dev->lock_state == RBD_LOCK_STATE_RELEASING &&
		       list_empty(&rbd_dev->running_list));
	spin_unlock(&rbd_dev->lock_lists_lock);
	if (need_wakeup)
		complete(&rbd_dev->releasing_wait);
}