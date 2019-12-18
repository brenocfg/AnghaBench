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
struct rbd_img_request {int /*<<< orphan*/  op_type; int /*<<< orphan*/  flags; int /*<<< orphan*/  state_mutex; struct rbd_device* rbd_dev; } ;
struct rbd_device {int /*<<< orphan*/  lock_rwsem; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMG_REQ_CHILD ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ need_exclusive_lock (struct rbd_img_request*) ; 
 int /*<<< orphan*/  obj_op_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbd_assert (int) ; 
 int rbd_img_advance (struct rbd_img_request*,int*) ; 
 int /*<<< orphan*/  rbd_lock_del_request (struct rbd_img_request*) ; 
 int /*<<< orphan*/  rbd_warn (struct rbd_device*,char*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool __rbd_img_handle_request(struct rbd_img_request *img_req,
				     int *result)
{
	struct rbd_device *rbd_dev = img_req->rbd_dev;
	bool done;

	if (need_exclusive_lock(img_req)) {
		down_read(&rbd_dev->lock_rwsem);
		mutex_lock(&img_req->state_mutex);
		done = rbd_img_advance(img_req, result);
		if (done)
			rbd_lock_del_request(img_req);
		mutex_unlock(&img_req->state_mutex);
		up_read(&rbd_dev->lock_rwsem);
	} else {
		mutex_lock(&img_req->state_mutex);
		done = rbd_img_advance(img_req, result);
		mutex_unlock(&img_req->state_mutex);
	}

	if (done && *result) {
		rbd_assert(*result < 0);
		rbd_warn(rbd_dev, "%s%s result %d",
		      test_bit(IMG_REQ_CHILD, &img_req->flags) ? "child " : "",
		      obj_op_name(img_req->op_type), *result);
	}
	return done;
}