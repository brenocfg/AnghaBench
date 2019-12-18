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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_6__ {int result; int /*<<< orphan*/  num_pending; } ;
struct rbd_obj_request {int flags; TYPE_3__ pending; TYPE_1__* img_request; } ;
struct TYPE_5__ {int features; } ;
struct rbd_device {TYPE_2__ header; } ;
struct ceph_snap_context {int num_snaps; int /*<<< orphan*/ * snaps; } ;
struct TYPE_4__ {struct ceph_snap_context* snapc; struct rbd_device* rbd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJECT_EXISTS ; 
 int /*<<< orphan*/  OBJECT_EXISTS_CLEAN ; 
 int RBD_FEATURE_FAST_DIFF ; 
 int RBD_FEATURE_OBJECT_MAP ; 
 int RBD_OBJ_FLAG_COPYUP_ZEROS ; 
 int /*<<< orphan*/  rbd_assert (int) ; 
 int rbd_object_map_update (struct rbd_obj_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rbd_obj_copyup_object_maps(struct rbd_obj_request *obj_req)
{
	struct rbd_device *rbd_dev = obj_req->img_request->rbd_dev;
	struct ceph_snap_context *snapc = obj_req->img_request->snapc;
	u8 new_state;
	u32 i;
	int ret;

	rbd_assert(!obj_req->pending.result && !obj_req->pending.num_pending);

	if (!(rbd_dev->header.features & RBD_FEATURE_OBJECT_MAP))
		return;

	if (obj_req->flags & RBD_OBJ_FLAG_COPYUP_ZEROS)
		return;

	for (i = 0; i < snapc->num_snaps; i++) {
		if ((rbd_dev->header.features & RBD_FEATURE_FAST_DIFF) &&
		    i + 1 < snapc->num_snaps)
			new_state = OBJECT_EXISTS_CLEAN;
		else
			new_state = OBJECT_EXISTS;

		ret = rbd_object_map_update(obj_req, snapc->snaps[i],
					    new_state, NULL);
		if (ret < 0) {
			obj_req->pending.result = ret;
			return;
		}

		rbd_assert(!ret);
		obj_req->pending.num_pending++;
	}
}