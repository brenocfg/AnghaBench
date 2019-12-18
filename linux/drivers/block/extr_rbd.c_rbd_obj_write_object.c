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
struct rbd_obj_request {int flags; } ;
struct ceph_osd_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 scalar_t__ IS_ERR (struct ceph_osd_request*) ; 
 int PTR_ERR (struct ceph_osd_request*) ; 
 int RBD_OBJ_FLAG_COPYUP_ENABLED ; 
 int ceph_osdc_alloc_messages (struct ceph_osd_request*,int /*<<< orphan*/ ) ; 
 int count_write_ops (struct rbd_obj_request*) ; 
 struct ceph_osd_request* rbd_obj_add_osd_request (struct rbd_obj_request*,int) ; 
 int /*<<< orphan*/  rbd_osd_format_write (struct ceph_osd_request*) ; 
 int rbd_osd_setup_stat (struct ceph_osd_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbd_osd_setup_write_ops (struct ceph_osd_request*,int) ; 
 int /*<<< orphan*/  rbd_osd_submit (struct ceph_osd_request*) ; 

__attribute__((used)) static int rbd_obj_write_object(struct rbd_obj_request *obj_req)
{
	struct ceph_osd_request *osd_req;
	int num_ops = count_write_ops(obj_req);
	int which = 0;
	int ret;

	if (obj_req->flags & RBD_OBJ_FLAG_COPYUP_ENABLED)
		num_ops++; /* stat */

	osd_req = rbd_obj_add_osd_request(obj_req, num_ops);
	if (IS_ERR(osd_req))
		return PTR_ERR(osd_req);

	if (obj_req->flags & RBD_OBJ_FLAG_COPYUP_ENABLED) {
		ret = rbd_osd_setup_stat(osd_req, which++);
		if (ret)
			return ret;
	}

	rbd_osd_setup_write_ops(osd_req, which);
	rbd_osd_format_write(osd_req);

	ret = ceph_osdc_alloc_messages(osd_req, GFP_NOIO);
	if (ret)
		return ret;

	rbd_osd_submit(osd_req);
	return 0;
}