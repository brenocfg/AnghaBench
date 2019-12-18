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
typedef  scalar_t__ u64 ;
struct rbd_device {int image_format; } ;

/* Variables and functions */
 scalar_t__ CEPH_NOSNAP ; 
 char const* RBD_SNAP_HEAD_NAME ; 
 int /*<<< orphan*/  rbd_assert (int /*<<< orphan*/ ) ; 
 char const* rbd_dev_v1_snap_name (struct rbd_device*,scalar_t__) ; 
 char const* rbd_dev_v2_snap_name (struct rbd_device*,scalar_t__) ; 
 int /*<<< orphan*/  rbd_image_format_valid (int) ; 

__attribute__((used)) static const char *rbd_snap_name(struct rbd_device *rbd_dev, u64 snap_id)
{
	if (snap_id == CEPH_NOSNAP)
		return RBD_SNAP_HEAD_NAME;

	rbd_assert(rbd_image_format_valid(rbd_dev->image_format));
	if (rbd_dev->image_format == 1)
		return rbd_dev_v1_snap_name(rbd_dev, snap_id);

	return rbd_dev_v2_snap_name(rbd_dev, snap_id);
}