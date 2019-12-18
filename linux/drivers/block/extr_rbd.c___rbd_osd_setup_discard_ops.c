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
struct TYPE_2__ {int /*<<< orphan*/  oe_len; int /*<<< orphan*/  oe_off; } ;
struct rbd_obj_request {int flags; TYPE_1__ ex; int /*<<< orphan*/  num_img_extents; } ;
struct ceph_osd_request {struct rbd_obj_request* r_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_OSD_OP_DELETE ; 
 int RBD_OBJ_FLAG_DELETION ; 
 int /*<<< orphan*/  osd_req_op_extent_init (struct ceph_osd_request*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osd_req_op_init (struct ceph_osd_request*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbd_assert (int) ; 
 scalar_t__ rbd_obj_is_entire (struct rbd_obj_request*) ; 
 int /*<<< orphan*/  truncate_or_zero_opcode (struct rbd_obj_request*) ; 

__attribute__((used)) static void __rbd_osd_setup_discard_ops(struct ceph_osd_request *osd_req,
					int which)
{
	struct rbd_obj_request *obj_req = osd_req->r_priv;

	if (rbd_obj_is_entire(obj_req) && !obj_req->num_img_extents) {
		rbd_assert(obj_req->flags & RBD_OBJ_FLAG_DELETION);
		osd_req_op_init(osd_req, which, CEPH_OSD_OP_DELETE, 0);
	} else {
		osd_req_op_extent_init(osd_req, which,
				       truncate_or_zero_opcode(obj_req),
				       obj_req->ex.oe_off, obj_req->ex.oe_len,
				       0, 0);
	}
}