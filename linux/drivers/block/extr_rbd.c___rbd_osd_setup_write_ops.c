#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {int /*<<< orphan*/  oe_len; int /*<<< orphan*/  oe_off; } ;
struct rbd_obj_request {int flags; TYPE_2__ ex; TYPE_3__* img_request; } ;
struct TYPE_4__ {int /*<<< orphan*/  object_size; } ;
struct rbd_device {TYPE_1__ layout; } ;
struct ceph_osd_request {struct rbd_obj_request* r_priv; } ;
struct TYPE_6__ {struct rbd_device* rbd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_OSD_OP_WRITE ; 
 int /*<<< orphan*/  CEPH_OSD_OP_WRITEFULL ; 
 int RBD_OBJ_FLAG_MAY_EXIST ; 
 int /*<<< orphan*/  osd_req_op_alloc_hint_init (struct ceph_osd_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osd_req_op_extent_init (struct ceph_osd_request*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rbd_obj_is_entire (struct rbd_obj_request*) ; 
 int /*<<< orphan*/  rbd_osd_setup_data (struct ceph_osd_request*,int) ; 
 int /*<<< orphan*/  use_object_map (struct rbd_device*) ; 

__attribute__((used)) static void __rbd_osd_setup_write_ops(struct ceph_osd_request *osd_req,
				      int which)
{
	struct rbd_obj_request *obj_req = osd_req->r_priv;
	struct rbd_device *rbd_dev = obj_req->img_request->rbd_dev;
	u16 opcode;

	if (!use_object_map(rbd_dev) ||
	    !(obj_req->flags & RBD_OBJ_FLAG_MAY_EXIST)) {
		osd_req_op_alloc_hint_init(osd_req, which++,
					   rbd_dev->layout.object_size,
					   rbd_dev->layout.object_size);
	}

	if (rbd_obj_is_entire(obj_req))
		opcode = CEPH_OSD_OP_WRITEFULL;
	else
		opcode = CEPH_OSD_OP_WRITE;

	osd_req_op_extent_init(osd_req, which, opcode,
			       obj_req->ex.oe_off, obj_req->ex.oe_len, 0, 0);
	rbd_osd_setup_data(osd_req, which);
}