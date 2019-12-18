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
struct TYPE_5__ {scalar_t__ oe_len; int /*<<< orphan*/  oe_off; } ;
struct rbd_obj_request {TYPE_2__ ex; TYPE_1__* img_request; } ;
struct TYPE_6__ {scalar_t__ object_size; } ;
struct rbd_device {TYPE_3__ layout; } ;
struct TYPE_4__ {struct rbd_device* rbd_dev; } ;

/* Variables and functions */

__attribute__((used)) static bool rbd_obj_is_entire(struct rbd_obj_request *obj_req)
{
	struct rbd_device *rbd_dev = obj_req->img_request->rbd_dev;

	return !obj_req->ex.oe_off &&
	       obj_req->ex.oe_len == rbd_dev->layout.object_size;
}