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
struct rbd_obj_request {int /*<<< orphan*/  num_img_extents; int /*<<< orphan*/  img_extents; TYPE_1__* img_request; } ;
struct rbd_device {int /*<<< orphan*/  parent_overlap; } ;
struct TYPE_2__ {struct rbd_device* rbd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODS_ONLY ; 
 int /*<<< orphan*/  prune_extents (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbd_assert (int /*<<< orphan*/ ) ; 
 int rbd_obj_copyup_current_snapc (struct rbd_obj_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbd_obj_img_extents_bytes (struct rbd_obj_request*) ; 
 int rbd_obj_read_from_parent (struct rbd_obj_request*) ; 
 int setup_copyup_bvecs (struct rbd_obj_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rbd_obj_copyup_read_parent(struct rbd_obj_request *obj_req)
{
	struct rbd_device *rbd_dev = obj_req->img_request->rbd_dev;
	int ret;

	rbd_assert(obj_req->num_img_extents);
	prune_extents(obj_req->img_extents, &obj_req->num_img_extents,
		      rbd_dev->parent_overlap);
	if (!obj_req->num_img_extents) {
		/*
		 * The overlap has become 0 (most likely because the
		 * image has been flattened).  Re-submit the original write
		 * request -- pass MODS_ONLY since the copyup isn't needed
		 * anymore.
		 */
		return rbd_obj_copyup_current_snapc(obj_req, MODS_ONLY);
	}

	ret = setup_copyup_bvecs(obj_req, rbd_obj_img_extents_bytes(obj_req));
	if (ret)
		return ret;

	return rbd_obj_read_from_parent(obj_req);
}