#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct rbd_obj_request {int flags; TYPE_1__* img_request; } ;
struct TYPE_4__ {int features; } ;
struct rbd_device {TYPE_2__ header; } ;
struct TYPE_3__ {struct rbd_device* rbd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_NOSNAP ; 
 int /*<<< orphan*/  OBJECT_NONEXISTENT ; 
 int /*<<< orphan*/  OBJECT_PENDING ; 
 int RBD_FEATURE_OBJECT_MAP ; 
 int RBD_OBJ_FLAG_DELETION ; 
 int rbd_object_map_update (struct rbd_obj_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rbd_obj_write_post_object_map(struct rbd_obj_request *obj_req)
{
	struct rbd_device *rbd_dev = obj_req->img_request->rbd_dev;
	u8 current_state = OBJECT_PENDING;

	if (!(rbd_dev->header.features & RBD_FEATURE_OBJECT_MAP))
		return 1;

	if (!(obj_req->flags & RBD_OBJ_FLAG_DELETION))
		return 1;

	return rbd_object_map_update(obj_req, CEPH_NOSNAP, OBJECT_NONEXISTENT,
				     &current_state);
}