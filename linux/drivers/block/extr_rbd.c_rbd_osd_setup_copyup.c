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
typedef  int /*<<< orphan*/  u32 ;
struct rbd_obj_request {int /*<<< orphan*/  copyup_bvec_count; int /*<<< orphan*/  copyup_bvecs; } ;
struct ceph_osd_request {struct rbd_obj_request* r_priv; } ;

/* Variables and functions */
 int osd_req_op_cls_init (struct ceph_osd_request*,int,char*,char*) ; 
 int /*<<< orphan*/  osd_req_op_cls_request_data_bvecs (struct ceph_osd_request*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rbd_osd_setup_copyup(struct ceph_osd_request *osd_req, int which,
				u32 bytes)
{
	struct rbd_obj_request *obj_req = osd_req->r_priv;
	int ret;

	ret = osd_req_op_cls_init(osd_req, which, "rbd", "copyup");
	if (ret)
		return ret;

	osd_req_op_cls_request_data_bvecs(osd_req, which, obj_req->copyup_bvecs,
					  obj_req->copyup_bvec_count, bytes);
	return 0;
}