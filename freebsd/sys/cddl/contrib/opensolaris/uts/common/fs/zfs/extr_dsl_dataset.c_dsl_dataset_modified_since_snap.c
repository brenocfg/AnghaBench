#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_15__ {TYPE_1__* os_phys; } ;
typedef  TYPE_3__ objset_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_16__ {int /*<<< orphan*/  ds_bp_rwlock; TYPE_2__* ds_dir; } ;
typedef  TYPE_4__ dsl_dataset_t ;
typedef  int boolean_t ;
struct TYPE_18__ {scalar_t__ blk_birth; } ;
struct TYPE_17__ {scalar_t__ ds_creation_txg; } ;
struct TYPE_14__ {int /*<<< orphan*/ * dd_pool; } ;
struct TYPE_13__ {int /*<<< orphan*/  os_meta_dnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int B_FALSE ; 
 int B_TRUE ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 scalar_t__ bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ dmu_objset_from_ds (TYPE_4__*,TYPE_3__**) ; 
 TYPE_9__* dsl_dataset_get_blkptr (TYPE_4__*) ; 
 TYPE_5__* dsl_dataset_phys (TYPE_4__*) ; 
 int /*<<< orphan*/  dsl_pool_config_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrw_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

boolean_t
dsl_dataset_modified_since_snap(dsl_dataset_t *ds, dsl_dataset_t *snap)
{
	dsl_pool_t *dp = ds->ds_dir->dd_pool;
	uint64_t birth;

	ASSERT(dsl_pool_config_held(dp));
	if (snap == NULL)
		return (B_FALSE);
	rrw_enter(&ds->ds_bp_rwlock, RW_READER, FTAG);
	birth = dsl_dataset_get_blkptr(ds)->blk_birth;
	rrw_exit(&ds->ds_bp_rwlock, FTAG);
	if (birth > dsl_dataset_phys(snap)->ds_creation_txg) {
		objset_t *os, *os_snap;
		/*
		 * It may be that only the ZIL differs, because it was
		 * reset in the head.  Don't count that as being
		 * modified.
		 */
		if (dmu_objset_from_ds(ds, &os) != 0)
			return (B_TRUE);
		if (dmu_objset_from_ds(snap, &os_snap) != 0)
			return (B_TRUE);
		return (bcmp(&os->os_phys->os_meta_dnode,
		    &os_snap->os_phys->os_meta_dnode,
		    sizeof (os->os_phys->os_meta_dnode)) != 0);
	}
	return (B_FALSE);
}