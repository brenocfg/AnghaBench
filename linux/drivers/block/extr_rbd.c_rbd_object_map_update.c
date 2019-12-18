#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_8__ {int /*<<< orphan*/  oe_objno; } ;
struct rbd_obj_request {TYPE_4__ ex; int /*<<< orphan*/  osd_reqs; TYPE_1__* img_request; } ;
struct rbd_device {int /*<<< orphan*/  header_oloc; TYPE_3__* rbd_client; } ;
struct ceph_osd_request {int /*<<< orphan*/  r_mtime; int /*<<< orphan*/  r_flags; int /*<<< orphan*/  r_base_oloc; int /*<<< orphan*/  r_base_oid; struct rbd_obj_request* r_priv; int /*<<< orphan*/  r_callback; int /*<<< orphan*/  r_private_item; } ;
struct ceph_osd_client {int dummy; } ;
struct TYPE_7__ {TYPE_2__* client; } ;
struct TYPE_6__ {struct ceph_osd_client osdc; } ;
struct TYPE_5__ {struct rbd_device* rbd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_CLS_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  CEPH_NOSNAP ; 
 int /*<<< orphan*/  CEPH_OSD_FLAG_WRITE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  RBD_LOCK_NAME ; 
 int ceph_cls_assert_locked (struct ceph_osd_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ceph_oloc_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ceph_osdc_alloc_messages (struct ceph_osd_request*,int /*<<< orphan*/ ) ; 
 struct ceph_osd_request* ceph_osdc_alloc_request (struct ceph_osd_client*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_osdc_start_request (struct ceph_osd_client*,struct ceph_osd_request*,int) ; 
 int /*<<< orphan*/  ktime_get_real_ts64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rbd_cls_object_map_update (struct ceph_osd_request*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  rbd_object_map_callback ; 
 int /*<<< orphan*/  rbd_object_map_name (struct rbd_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_needed (struct rbd_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rbd_object_map_update(struct rbd_obj_request *obj_req, u64 snap_id,
				 u8 new_state, const u8 *current_state)
{
	struct rbd_device *rbd_dev = obj_req->img_request->rbd_dev;
	struct ceph_osd_client *osdc = &rbd_dev->rbd_client->client->osdc;
	struct ceph_osd_request *req;
	int num_ops = 1;
	int which = 0;
	int ret;

	if (snap_id == CEPH_NOSNAP) {
		if (!update_needed(rbd_dev, obj_req->ex.oe_objno, new_state))
			return 1;

		num_ops++; /* assert_locked */
	}

	req = ceph_osdc_alloc_request(osdc, NULL, num_ops, false, GFP_NOIO);
	if (!req)
		return -ENOMEM;

	list_add_tail(&req->r_private_item, &obj_req->osd_reqs);
	req->r_callback = rbd_object_map_callback;
	req->r_priv = obj_req;

	rbd_object_map_name(rbd_dev, snap_id, &req->r_base_oid);
	ceph_oloc_copy(&req->r_base_oloc, &rbd_dev->header_oloc);
	req->r_flags = CEPH_OSD_FLAG_WRITE;
	ktime_get_real_ts64(&req->r_mtime);

	if (snap_id == CEPH_NOSNAP) {
		/*
		 * Protect against possible race conditions during lock
		 * ownership transitions.
		 */
		ret = ceph_cls_assert_locked(req, which++, RBD_LOCK_NAME,
					     CEPH_CLS_LOCK_EXCLUSIVE, "", "");
		if (ret)
			return ret;
	}

	ret = rbd_cls_object_map_update(req, which, obj_req->ex.oe_objno,
					new_state, current_state);
	if (ret)
		return ret;

	ret = ceph_osdc_alloc_messages(req, GFP_NOIO);
	if (ret)
		return ret;

	ceph_osdc_start_request(osdc, req, false);
	return 0;
}