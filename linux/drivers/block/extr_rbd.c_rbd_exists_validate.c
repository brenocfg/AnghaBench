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
typedef  scalar_t__ u64 ;
struct rbd_device {int /*<<< orphan*/  flags; TYPE_1__* spec; } ;
struct TYPE_2__ {scalar_t__ snap_id; } ;

/* Variables and functions */
 scalar_t__ BAD_SNAP_INDEX ; 
 scalar_t__ CEPH_NOSNAP ; 
 int /*<<< orphan*/  RBD_DEV_FLAG_EXISTS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ rbd_dev_snap_index (struct rbd_device*,scalar_t__) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rbd_exists_validate(struct rbd_device *rbd_dev)
{
	u64 snap_id;

	if (!test_bit(RBD_DEV_FLAG_EXISTS, &rbd_dev->flags))
		return;

	snap_id = rbd_dev->spec->snap_id;
	if (snap_id == CEPH_NOSNAP)
		return;

	if (rbd_dev_snap_index(rbd_dev, snap_id) == BAD_SNAP_INDEX)
		clear_bit(RBD_DEV_FLAG_EXISTS, &rbd_dev->flags);
}