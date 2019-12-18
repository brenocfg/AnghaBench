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
struct rbd_obj_request {TYPE_2__* img_request; int /*<<< orphan*/  num_img_extents; } ;
struct TYPE_4__ {TYPE_1__* snapc; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_snaps; } ;

/* Variables and functions */
 scalar_t__ rbd_obj_is_entire (struct rbd_obj_request*) ; 

__attribute__((used)) static bool rbd_obj_copyup_enabled(struct rbd_obj_request *obj_req)
{
	if (!obj_req->num_img_extents ||
	    (rbd_obj_is_entire(obj_req) &&
	     !obj_req->img_request->snapc->num_snaps))
		return false;

	return true;
}