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
typedef  scalar_t__ u32 ;
struct TYPE_6__ {int result; int /*<<< orphan*/  num_pending; } ;
struct rbd_obj_request {int flags; TYPE_3__ pending; TYPE_2__* img_request; } ;
struct TYPE_5__ {TYPE_1__* snapc; } ;
struct TYPE_4__ {scalar_t__ num_snaps; } ;

/* Variables and functions */
 scalar_t__ MODS_ONLY ; 
 int RBD_OBJ_FLAG_COPYUP_ZEROS ; 
 int /*<<< orphan*/  rbd_assert (int) ; 
 int rbd_obj_copyup_current_snapc (struct rbd_obj_request*,scalar_t__) ; 
 int rbd_obj_copyup_empty_snapc (struct rbd_obj_request*,scalar_t__) ; 
 scalar_t__ rbd_obj_img_extents_bytes (struct rbd_obj_request*) ; 

__attribute__((used)) static void rbd_obj_copyup_write_object(struct rbd_obj_request *obj_req)
{
	u32 bytes = rbd_obj_img_extents_bytes(obj_req);
	int ret;

	rbd_assert(!obj_req->pending.result && !obj_req->pending.num_pending);

	/*
	 * Only send non-zero copyup data to save some I/O and network
	 * bandwidth -- zero copyup data is equivalent to the object not
	 * existing.
	 */
	if (obj_req->flags & RBD_OBJ_FLAG_COPYUP_ZEROS)
		bytes = 0;

	if (obj_req->img_request->snapc->num_snaps && bytes > 0) {
		/*
		 * Send a copyup request with an empty snapshot context to
		 * deep-copyup the object through all existing snapshots.
		 * A second request with the current snapshot context will be
		 * sent for the actual modification.
		 */
		ret = rbd_obj_copyup_empty_snapc(obj_req, bytes);
		if (ret) {
			obj_req->pending.result = ret;
			return;
		}

		obj_req->pending.num_pending++;
		bytes = MODS_ONLY;
	}

	ret = rbd_obj_copyup_current_snapc(obj_req, bytes);
	if (ret) {
		obj_req->pending.result = ret;
		return;
	}

	obj_req->pending.num_pending++;
}