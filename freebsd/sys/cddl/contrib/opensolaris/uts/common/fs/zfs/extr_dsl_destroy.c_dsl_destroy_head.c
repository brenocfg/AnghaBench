#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_4__ {char const* ddha_name; } ;
typedef  TYPE_1__ dsl_destroy_head_arg_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  ds_prev_snap_txg; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  DMU_OST_ANY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  SPA_FEATURE_ASYNC_DESTROY ; 
 int /*<<< orphan*/  ZFS_SPACE_CHECK_DESTROY ; 
 int /*<<< orphan*/  dmu_free_long_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dmu_object_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_objset_disown (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_objset_ds (int /*<<< orphan*/ *) ; 
 int dmu_objset_own (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dmu_objset_pool (int /*<<< orphan*/ *) ; 
 TYPE_3__* dsl_dataset_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_destroy_head_begin_sync ; 
 int /*<<< orphan*/  dsl_destroy_head_check ; 
 int /*<<< orphan*/  dsl_destroy_head_sync ; 
 int dsl_sync_task (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_feature_is_enabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spa_open (char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_destroy_unmount_origin (char const*) ; 

int
dsl_destroy_head(const char *name)
{
	dsl_destroy_head_arg_t ddha;
	int error;
	spa_t *spa;
	boolean_t isenabled;

#ifdef _KERNEL
	zfs_destroy_unmount_origin(name);
#endif

	error = spa_open(name, &spa, FTAG);
	if (error != 0)
		return (error);
	isenabled = spa_feature_is_enabled(spa, SPA_FEATURE_ASYNC_DESTROY);
	spa_close(spa, FTAG);

	ddha.ddha_name = name;

	if (!isenabled) {
		objset_t *os;

		error = dsl_sync_task(name, dsl_destroy_head_check,
		    dsl_destroy_head_begin_sync, &ddha,
		    0, ZFS_SPACE_CHECK_DESTROY);
		if (error != 0)
			return (error);

		/*
		 * Head deletion is processed in one txg on old pools;
		 * remove the objects from open context so that the txg sync
		 * is not too long.
		 */
		error = dmu_objset_own(name, DMU_OST_ANY, B_FALSE, FTAG, &os);
		if (error == 0) {
			uint64_t prev_snap_txg =
			    dsl_dataset_phys(dmu_objset_ds(os))->
			    ds_prev_snap_txg;
			for (uint64_t obj = 0; error == 0;
			    error = dmu_object_next(os, &obj, FALSE,
			    prev_snap_txg))
				(void) dmu_free_long_object(os, obj);
			/* sync out all frees */
			txg_wait_synced(dmu_objset_pool(os), 0);
			dmu_objset_disown(os, FTAG);
		}
	}

	return (dsl_sync_task(name, dsl_destroy_head_check,
	    dsl_destroy_head_sync, &ddha, 0, ZFS_SPACE_CHECK_DESTROY));
}