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
typedef  int u32 ;
struct TYPE_4__ {int oe_len; } ;
struct rbd_obj_request {int read_state; TYPE_2__ ex; int /*<<< orphan*/  num_img_extents; TYPE_1__* img_request; } ;
struct rbd_device {int /*<<< orphan*/  parent_overlap; } ;
struct TYPE_3__ {struct rbd_device* rbd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int ENOENT ; 
#define  RBD_OBJ_READ_OBJECT 130 
#define  RBD_OBJ_READ_PARENT 129 
#define  RBD_OBJ_READ_START 128 
 int /*<<< orphan*/  rbd_assert (int) ; 
 int rbd_obj_calc_img_extents (struct rbd_obj_request*,int) ; 
 int rbd_obj_img_extents_bytes (struct rbd_obj_request*) ; 
 int /*<<< orphan*/  rbd_obj_may_exist (struct rbd_obj_request*) ; 
 int rbd_obj_read_from_parent (struct rbd_obj_request*) ; 
 int rbd_obj_read_object (struct rbd_obj_request*) ; 
 int /*<<< orphan*/  rbd_obj_zero_range (struct rbd_obj_request*,int,int) ; 

__attribute__((used)) static bool rbd_obj_advance_read(struct rbd_obj_request *obj_req, int *result)
{
	struct rbd_device *rbd_dev = obj_req->img_request->rbd_dev;
	int ret;

again:
	switch (obj_req->read_state) {
	case RBD_OBJ_READ_START:
		rbd_assert(!*result);

		if (!rbd_obj_may_exist(obj_req)) {
			*result = -ENOENT;
			obj_req->read_state = RBD_OBJ_READ_OBJECT;
			goto again;
		}

		ret = rbd_obj_read_object(obj_req);
		if (ret) {
			*result = ret;
			return true;
		}
		obj_req->read_state = RBD_OBJ_READ_OBJECT;
		return false;
	case RBD_OBJ_READ_OBJECT:
		if (*result == -ENOENT && rbd_dev->parent_overlap) {
			/* reverse map this object extent onto the parent */
			ret = rbd_obj_calc_img_extents(obj_req, false);
			if (ret) {
				*result = ret;
				return true;
			}
			if (obj_req->num_img_extents) {
				ret = rbd_obj_read_from_parent(obj_req);
				if (ret) {
					*result = ret;
					return true;
				}
				obj_req->read_state = RBD_OBJ_READ_PARENT;
				return false;
			}
		}

		/*
		 * -ENOENT means a hole in the image -- zero-fill the entire
		 * length of the request.  A short read also implies zero-fill
		 * to the end of the request.
		 */
		if (*result == -ENOENT) {
			rbd_obj_zero_range(obj_req, 0, obj_req->ex.oe_len);
			*result = 0;
		} else if (*result >= 0) {
			if (*result < obj_req->ex.oe_len)
				rbd_obj_zero_range(obj_req, *result,
						obj_req->ex.oe_len - *result);
			else
				rbd_assert(*result == obj_req->ex.oe_len);
			*result = 0;
		}
		return true;
	case RBD_OBJ_READ_PARENT:
		/*
		 * The parent image is read only up to the overlap -- zero-fill
		 * from the overlap to the end of the request.
		 */
		if (!*result) {
			u32 obj_overlap = rbd_obj_img_extents_bytes(obj_req);

			if (obj_overlap < obj_req->ex.oe_len)
				rbd_obj_zero_range(obj_req, obj_overlap,
					    obj_req->ex.oe_len - obj_overlap);
		}
		return true;
	default:
		BUG();
	}
}