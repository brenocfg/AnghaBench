#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_17__ {int /*<<< orphan*/  dd_lock; } ;
typedef  TYPE_1__ dsl_dir_t ;
struct TYPE_18__ {int dd_flags; } ;

/* Variables and functions */
 int DD_FLAG_USED_BREAKDOWN ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_PROP_FILESYSTEM_COUNT ; 
 int /*<<< orphan*/  ZFS_PROP_LOGICALUSED ; 
 int /*<<< orphan*/  ZFS_PROP_ORIGIN ; 
 int /*<<< orphan*/  ZFS_PROP_QUOTA ; 
 int /*<<< orphan*/  ZFS_PROP_REMAPTXG ; 
 int /*<<< orphan*/  ZFS_PROP_RESERVATION ; 
 int /*<<< orphan*/  ZFS_PROP_SNAPSHOT_COUNT ; 
 int /*<<< orphan*/  ZFS_PROP_USEDCHILD ; 
 int /*<<< orphan*/  ZFS_PROP_USEDDS ; 
 int /*<<< orphan*/  ZFS_PROP_USEDREFRESERV ; 
 int /*<<< orphan*/  ZFS_PROP_USEDSNAP ; 
 scalar_t__ dsl_dir_get_filesystem_count (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_get_logicalused (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_dir_get_origin (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dsl_dir_get_quota (TYPE_1__*) ; 
 scalar_t__ dsl_dir_get_remaptxg (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_get_reservation (TYPE_1__*) ; 
 scalar_t__ dsl_dir_get_snapshot_count (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_get_usedchild (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_dir_get_usedds (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_dir_get_usedrefreserv (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_dir_get_usedsnap (TYPE_1__*) ; 
 scalar_t__ dsl_dir_is_clone (TYPE_1__*) ; 
 TYPE_3__* dsl_dir_phys (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_prop_nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dsl_prop_nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
dsl_dir_stats(dsl_dir_t *dd, nvlist_t *nv)
{
	mutex_enter(&dd->dd_lock);
	dsl_prop_nvlist_add_uint64(nv, ZFS_PROP_QUOTA,
	    dsl_dir_get_quota(dd));
	dsl_prop_nvlist_add_uint64(nv, ZFS_PROP_RESERVATION,
	    dsl_dir_get_reservation(dd));
	dsl_prop_nvlist_add_uint64(nv, ZFS_PROP_LOGICALUSED,
	    dsl_dir_get_logicalused(dd));
	if (dsl_dir_phys(dd)->dd_flags & DD_FLAG_USED_BREAKDOWN) {
		dsl_prop_nvlist_add_uint64(nv, ZFS_PROP_USEDSNAP,
		    dsl_dir_get_usedsnap(dd));
		dsl_prop_nvlist_add_uint64(nv, ZFS_PROP_USEDDS,
		    dsl_dir_get_usedds(dd));
		dsl_prop_nvlist_add_uint64(nv, ZFS_PROP_USEDREFRESERV,
		    dsl_dir_get_usedrefreserv(dd));
		dsl_prop_nvlist_add_uint64(nv, ZFS_PROP_USEDCHILD,
		    dsl_dir_get_usedchild(dd));
	}
	mutex_exit(&dd->dd_lock);

	uint64_t count;
	if (dsl_dir_get_filesystem_count(dd, &count) == 0) {
		dsl_prop_nvlist_add_uint64(nv, ZFS_PROP_FILESYSTEM_COUNT,
		    count);
	}
	if (dsl_dir_get_snapshot_count(dd, &count) == 0) {
		dsl_prop_nvlist_add_uint64(nv, ZFS_PROP_SNAPSHOT_COUNT,
		    count);
	}
	if (dsl_dir_get_remaptxg(dd, &count) == 0) {
		dsl_prop_nvlist_add_uint64(nv, ZFS_PROP_REMAPTXG,
		    count);
	}

	if (dsl_dir_is_clone(dd)) {
		char buf[ZFS_MAX_DATASET_NAME_LEN];
		dsl_dir_get_origin(dd, buf);
		dsl_prop_nvlist_add_string(nv, ZFS_PROP_ORIGIN, buf);
	}

}