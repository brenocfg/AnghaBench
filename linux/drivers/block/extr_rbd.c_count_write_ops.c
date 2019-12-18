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
struct rbd_obj_request {int flags; int /*<<< orphan*/  num_img_extents; struct rbd_img_request* img_request; } ;
struct rbd_img_request {int op_type; int /*<<< orphan*/  rbd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  OBJ_OP_DISCARD 130 
#define  OBJ_OP_WRITE 129 
#define  OBJ_OP_ZEROOUT 128 
 int RBD_OBJ_FLAG_COPYUP_ENABLED ; 
 int RBD_OBJ_FLAG_MAY_EXIST ; 
 int /*<<< orphan*/  rbd_obj_is_entire (struct rbd_obj_request*) ; 
 int /*<<< orphan*/  use_object_map (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int count_write_ops(struct rbd_obj_request *obj_req)
{
	struct rbd_img_request *img_req = obj_req->img_request;

	switch (img_req->op_type) {
	case OBJ_OP_WRITE:
		if (!use_object_map(img_req->rbd_dev) ||
		    !(obj_req->flags & RBD_OBJ_FLAG_MAY_EXIST))
			return 2; /* setallochint + write/writefull */

		return 1; /* write/writefull */
	case OBJ_OP_DISCARD:
		return 1; /* delete/truncate/zero */
	case OBJ_OP_ZEROOUT:
		if (rbd_obj_is_entire(obj_req) && obj_req->num_img_extents &&
		    !(obj_req->flags & RBD_OBJ_FLAG_COPYUP_ENABLED))
			return 2; /* create + truncate */

		return 1; /* delete/truncate/zero */
	default:
		BUG();
	}
}