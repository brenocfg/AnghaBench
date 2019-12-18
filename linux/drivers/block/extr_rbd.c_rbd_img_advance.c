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
struct TYPE_2__ {int result; int /*<<< orphan*/  num_pending; } ;
struct rbd_img_request {int state; TYPE_1__ pending; struct rbd_device* rbd_dev; } ;
struct rbd_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  RBD_IMG_EXCLUSIVE_LOCK 131 
#define  RBD_IMG_OBJECT_REQUESTS 130 
#define  RBD_IMG_START 129 
#define  __RBD_IMG_OBJECT_REQUESTS 128 
 int /*<<< orphan*/  __rbd_is_lock_owner (struct rbd_device*) ; 
 int /*<<< orphan*/  need_exclusive_lock (struct rbd_img_request*) ; 
 int /*<<< orphan*/  pending_result_dec (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  rbd_assert (int) ; 
 int rbd_img_exclusive_lock (struct rbd_img_request*) ; 
 int /*<<< orphan*/  rbd_img_object_requests (struct rbd_img_request*) ; 

__attribute__((used)) static bool rbd_img_advance(struct rbd_img_request *img_req, int *result)
{
	struct rbd_device *rbd_dev = img_req->rbd_dev;
	int ret;

again:
	switch (img_req->state) {
	case RBD_IMG_START:
		rbd_assert(!*result);

		ret = rbd_img_exclusive_lock(img_req);
		if (ret < 0) {
			*result = ret;
			return true;
		}
		img_req->state = RBD_IMG_EXCLUSIVE_LOCK;
		if (ret > 0)
			goto again;
		return false;
	case RBD_IMG_EXCLUSIVE_LOCK:
		if (*result)
			return true;

		rbd_assert(!need_exclusive_lock(img_req) ||
			   __rbd_is_lock_owner(rbd_dev));

		rbd_img_object_requests(img_req);
		if (!img_req->pending.num_pending) {
			*result = img_req->pending.result;
			img_req->state = RBD_IMG_OBJECT_REQUESTS;
			goto again;
		}
		img_req->state = __RBD_IMG_OBJECT_REQUESTS;
		return false;
	case __RBD_IMG_OBJECT_REQUESTS:
		if (!pending_result_dec(&img_req->pending, result))
			return false;
		/* fall through */
	case RBD_IMG_OBJECT_REQUESTS:
		return true;
	default:
		BUG();
	}
}