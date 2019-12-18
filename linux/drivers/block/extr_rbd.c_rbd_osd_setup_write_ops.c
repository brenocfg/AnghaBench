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
struct rbd_obj_request {TYPE_1__* img_request; } ;
struct ceph_osd_request {struct rbd_obj_request* r_priv; } ;
struct TYPE_2__ {int op_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  OBJ_OP_DISCARD 130 
#define  OBJ_OP_WRITE 129 
#define  OBJ_OP_ZEROOUT 128 
 int /*<<< orphan*/  __rbd_osd_setup_discard_ops (struct ceph_osd_request*,int) ; 
 int /*<<< orphan*/  __rbd_osd_setup_write_ops (struct ceph_osd_request*,int) ; 
 int /*<<< orphan*/  __rbd_osd_setup_zeroout_ops (struct ceph_osd_request*,int) ; 

__attribute__((used)) static void rbd_osd_setup_write_ops(struct ceph_osd_request *osd_req,
				    int which)
{
	struct rbd_obj_request *obj_req = osd_req->r_priv;

	switch (obj_req->img_request->op_type) {
	case OBJ_OP_WRITE:
		__rbd_osd_setup_write_ops(osd_req, which);
		break;
	case OBJ_OP_DISCARD:
		__rbd_osd_setup_discard_ops(osd_req, which);
		break;
	case OBJ_OP_ZEROOUT:
		__rbd_osd_setup_zeroout_ops(osd_req, which);
		break;
	default:
		BUG();
	}
}