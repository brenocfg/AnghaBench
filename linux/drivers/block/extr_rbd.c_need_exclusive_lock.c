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
struct rbd_img_request {int /*<<< orphan*/  flags; struct rbd_device* rbd_dev; } ;
struct TYPE_6__ {int features; } ;
struct rbd_device {TYPE_3__ header; TYPE_2__* opts; TYPE_1__* spec; } ;
struct TYPE_5__ {scalar_t__ lock_on_read; } ;
struct TYPE_4__ {scalar_t__ snap_id; } ;

/* Variables and functions */
 scalar_t__ CEPH_NOSNAP ; 
 int /*<<< orphan*/  IMG_REQ_CHILD ; 
 int RBD_FEATURE_EXCLUSIVE_LOCK ; 
 int RBD_FEATURE_OBJECT_MAP ; 
 int /*<<< orphan*/  rbd_assert (int) ; 
 int rbd_img_is_write (struct rbd_img_request*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool need_exclusive_lock(struct rbd_img_request *img_req)
{
	struct rbd_device *rbd_dev = img_req->rbd_dev;

	if (!(rbd_dev->header.features & RBD_FEATURE_EXCLUSIVE_LOCK))
		return false;

	if (rbd_dev->spec->snap_id != CEPH_NOSNAP)
		return false;

	rbd_assert(!test_bit(IMG_REQ_CHILD, &img_req->flags));
	if (rbd_dev->opts->lock_on_read ||
	    (rbd_dev->header.features & RBD_FEATURE_OBJECT_MAP))
		return true;

	return rbd_img_is_write(img_req);
}