#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_10__ {scalar_t__ ds_object; int /*<<< orphan*/  ds_deadlist; TYPE_1__* ds_dir; } ;
typedef  TYPE_2__ dsl_dataset_t ;
struct TYPE_11__ {scalar_t__ ds_referenced_bytes; scalar_t__ ds_compressed_bytes; scalar_t__ ds_uncompressed_bytes; scalar_t__ ds_prev_snap_txg; scalar_t__ ds_creation_txg; scalar_t__ ds_prev_snap_obj; } ;
struct TYPE_9__ {int /*<<< orphan*/ * dd_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int dsl_dataset_hold_obj (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,TYPE_2__**) ; 
 TYPE_6__* dsl_dataset_phys (TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_deadlist_space (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  dsl_deadlist_space_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  dsl_pool_config_held (int /*<<< orphan*/ *) ; 

int
dsl_dataset_space_written(dsl_dataset_t *oldsnap, dsl_dataset_t *new,
    uint64_t *usedp, uint64_t *compp, uint64_t *uncompp)
{
	int err = 0;
	uint64_t snapobj;
	dsl_pool_t *dp = new->ds_dir->dd_pool;

	ASSERT(dsl_pool_config_held(dp));

	*usedp = 0;
	*usedp += dsl_dataset_phys(new)->ds_referenced_bytes;
	*usedp -= dsl_dataset_phys(oldsnap)->ds_referenced_bytes;

	*compp = 0;
	*compp += dsl_dataset_phys(new)->ds_compressed_bytes;
	*compp -= dsl_dataset_phys(oldsnap)->ds_compressed_bytes;

	*uncompp = 0;
	*uncompp += dsl_dataset_phys(new)->ds_uncompressed_bytes;
	*uncompp -= dsl_dataset_phys(oldsnap)->ds_uncompressed_bytes;

	snapobj = new->ds_object;
	while (snapobj != oldsnap->ds_object) {
		dsl_dataset_t *snap;
		uint64_t used, comp, uncomp;

		if (snapobj == new->ds_object) {
			snap = new;
		} else {
			err = dsl_dataset_hold_obj(dp, snapobj, FTAG, &snap);
			if (err != 0)
				break;
		}

		if (dsl_dataset_phys(snap)->ds_prev_snap_txg ==
		    dsl_dataset_phys(oldsnap)->ds_creation_txg) {
			/*
			 * The blocks in the deadlist can not be born after
			 * ds_prev_snap_txg, so get the whole deadlist space,
			 * which is more efficient (especially for old-format
			 * deadlists).  Unfortunately the deadlist code
			 * doesn't have enough information to make this
			 * optimization itself.
			 */
			dsl_deadlist_space(&snap->ds_deadlist,
			    &used, &comp, &uncomp);
		} else {
			dsl_deadlist_space_range(&snap->ds_deadlist,
			    0, dsl_dataset_phys(oldsnap)->ds_creation_txg,
			    &used, &comp, &uncomp);
		}
		*usedp += used;
		*compp += comp;
		*uncompp += uncomp;

		/*
		 * If we get to the beginning of the chain of snapshots
		 * (ds_prev_snap_obj == 0) before oldsnap, then oldsnap
		 * was not a snapshot of/before new.
		 */
		snapobj = dsl_dataset_phys(snap)->ds_prev_snap_obj;
		if (snap != new)
			dsl_dataset_rele(snap, FTAG);
		if (snapobj == 0) {
			err = SET_ERROR(EINVAL);
			break;
		}

	}
	return (err);
}