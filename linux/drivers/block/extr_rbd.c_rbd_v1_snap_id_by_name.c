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
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct TYPE_2__ {char* snap_names; struct ceph_snap_context* snapc; } ;
struct rbd_device {TYPE_1__ header; } ;
struct ceph_snap_context {size_t num_snaps; int /*<<< orphan*/ * snaps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_NOSNAP ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static u64 rbd_v1_snap_id_by_name(struct rbd_device *rbd_dev, const char *name)
{
	struct ceph_snap_context *snapc = rbd_dev->header.snapc;
	const char *snap_name;
	u32 which = 0;

	/* Skip over names until we find the one we are looking for */

	snap_name = rbd_dev->header.snap_names;
	while (which < snapc->num_snaps) {
		if (!strcmp(name, snap_name))
			return snapc->snaps[which];
		snap_name += strlen(snap_name) + 1;
		which++;
	}
	return CEPH_NOSNAP;
}