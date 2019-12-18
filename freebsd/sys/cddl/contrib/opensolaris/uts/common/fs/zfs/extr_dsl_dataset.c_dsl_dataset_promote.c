#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
struct TYPE_5__ {char const* ddpa_clonename; int /*<<< orphan*/  err_ds; int /*<<< orphan*/  cr; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ dsl_dataset_promote_arg_t ;
struct TYPE_7__ {int /*<<< orphan*/  dp_meta_objset; } ;
struct TYPE_6__ {int /*<<< orphan*/  ds_snapnames_zapobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRED () ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  ZFS_SPACE_CHECK_RESERVED ; 
 int /*<<< orphan*/  dmu_objset_ds (int /*<<< orphan*/ *) ; 
 int dmu_objset_hold (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 TYPE_4__* dmu_objset_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* dsl_dataset_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_promote_check ; 
 int /*<<< orphan*/  dsl_dataset_promote_sync ; 
 int dsl_sync_task (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int zap_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

int
dsl_dataset_promote(const char *name, char *conflsnap)
{
	dsl_dataset_promote_arg_t ddpa = { 0 };
	uint64_t numsnaps;
	int error;
	nvpair_t *snap_pair;
	objset_t *os;

	/*
	 * We will modify space proportional to the number of
	 * snapshots.  Compute numsnaps.
	 */
	error = dmu_objset_hold(name, FTAG, &os);
	if (error != 0)
		return (error);
	error = zap_count(dmu_objset_pool(os)->dp_meta_objset,
	    dsl_dataset_phys(dmu_objset_ds(os))->ds_snapnames_zapobj,
	    &numsnaps);
	dmu_objset_rele(os, FTAG);
	if (error != 0)
		return (error);

	ddpa.ddpa_clonename = name;
	ddpa.err_ds = fnvlist_alloc();
	ddpa.cr = CRED();

	error = dsl_sync_task(name, dsl_dataset_promote_check,
	    dsl_dataset_promote_sync, &ddpa,
	    2 + numsnaps, ZFS_SPACE_CHECK_RESERVED);

	/*
	 * Return the first conflicting snapshot found.
	 */
	snap_pair = nvlist_next_nvpair(ddpa.err_ds, NULL);
	if (snap_pair != NULL && conflsnap != NULL)
		(void) strcpy(conflsnap, nvpair_name(snap_pair));

	fnvlist_free(ddpa.err_ds);
	return (error);
}