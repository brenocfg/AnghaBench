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
struct rbd_obj_request {int write_state; int flags; int /*<<< orphan*/  copyup_state; TYPE_1__* img_request; } ;
struct rbd_device {int dummy; } ;
struct TYPE_2__ {struct rbd_device* rbd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int ENOENT ; 
 int /*<<< orphan*/  RBD_OBJ_COPYUP_START ; 
 int RBD_OBJ_FLAG_COPYUP_ENABLED ; 
 int RBD_OBJ_FLAG_DELETION ; 
#define  RBD_OBJ_WRITE_COPYUP 133 
#define  RBD_OBJ_WRITE_OBJECT 132 
#define  RBD_OBJ_WRITE_POST_OBJECT_MAP 131 
#define  RBD_OBJ_WRITE_PRE_OBJECT_MAP 130 
#define  RBD_OBJ_WRITE_START 129 
#define  __RBD_OBJ_WRITE_COPYUP 128 
 int /*<<< orphan*/  rbd_assert (int) ; 
 int /*<<< orphan*/  rbd_obj_advance_copyup (struct rbd_obj_request*,int*) ; 
 int /*<<< orphan*/  rbd_obj_write_is_noop (struct rbd_obj_request*) ; 
 int rbd_obj_write_object (struct rbd_obj_request*) ; 
 int rbd_obj_write_post_object_map (struct rbd_obj_request*) ; 
 int rbd_obj_write_pre_object_map (struct rbd_obj_request*) ; 
 int /*<<< orphan*/  rbd_warn (struct rbd_device*,char*,int) ; 

__attribute__((used)) static bool rbd_obj_advance_write(struct rbd_obj_request *obj_req, int *result)
{
	struct rbd_device *rbd_dev = obj_req->img_request->rbd_dev;
	int ret;

again:
	switch (obj_req->write_state) {
	case RBD_OBJ_WRITE_START:
		rbd_assert(!*result);

		if (rbd_obj_write_is_noop(obj_req))
			return true;

		ret = rbd_obj_write_pre_object_map(obj_req);
		if (ret < 0) {
			*result = ret;
			return true;
		}
		obj_req->write_state = RBD_OBJ_WRITE_PRE_OBJECT_MAP;
		if (ret > 0)
			goto again;
		return false;
	case RBD_OBJ_WRITE_PRE_OBJECT_MAP:
		if (*result) {
			rbd_warn(rbd_dev, "pre object map update failed: %d",
				 *result);
			return true;
		}
		ret = rbd_obj_write_object(obj_req);
		if (ret) {
			*result = ret;
			return true;
		}
		obj_req->write_state = RBD_OBJ_WRITE_OBJECT;
		return false;
	case RBD_OBJ_WRITE_OBJECT:
		if (*result == -ENOENT) {
			if (obj_req->flags & RBD_OBJ_FLAG_COPYUP_ENABLED) {
				*result = 0;
				obj_req->copyup_state = RBD_OBJ_COPYUP_START;
				obj_req->write_state = __RBD_OBJ_WRITE_COPYUP;
				goto again;
			}
			/*
			 * On a non-existent object:
			 *   delete - -ENOENT, truncate/zero - 0
			 */
			if (obj_req->flags & RBD_OBJ_FLAG_DELETION)
				*result = 0;
		}
		if (*result)
			return true;

		obj_req->write_state = RBD_OBJ_WRITE_COPYUP;
		goto again;
	case __RBD_OBJ_WRITE_COPYUP:
		if (!rbd_obj_advance_copyup(obj_req, result))
			return false;
		/* fall through */
	case RBD_OBJ_WRITE_COPYUP:
		if (*result) {
			rbd_warn(rbd_dev, "copyup failed: %d", *result);
			return true;
		}
		ret = rbd_obj_write_post_object_map(obj_req);
		if (ret < 0) {
			*result = ret;
			return true;
		}
		obj_req->write_state = RBD_OBJ_WRITE_POST_OBJECT_MAP;
		if (ret > 0)
			goto again;
		return false;
	case RBD_OBJ_WRITE_POST_OBJECT_MAP:
		if (*result)
			rbd_warn(rbd_dev, "post object map update failed: %d",
				 *result);
		return true;
	default:
		BUG();
	}
}