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
struct rbd_device {TYPE_1__* spec; } ;
struct ceph_object_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  image_id; } ;

/* Variables and functions */
 scalar_t__ CEPH_NOSNAP ; 
 int /*<<< orphan*/  RBD_OBJECT_MAP_PREFIX ; 
 int /*<<< orphan*/  ceph_oid_printf (struct ceph_object_id*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void rbd_object_map_name(struct rbd_device *rbd_dev, u64 snap_id,
				struct ceph_object_id *oid)
{
	if (snap_id == CEPH_NOSNAP)
		ceph_oid_printf(oid, "%s%s", RBD_OBJECT_MAP_PREFIX,
				rbd_dev->spec->image_id);
	else
		ceph_oid_printf(oid, "%s%s.%016llx", RBD_OBJECT_MAP_PREFIX,
				rbd_dev->spec->image_id, snap_id);
}