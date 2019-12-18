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
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int matchtype_t ;
struct TYPE_9__ {TYPE_3__* ds_dir; } ;
typedef  TYPE_2__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_11__ {int ds_flags; int /*<<< orphan*/  ds_snapnames_zapobj; } ;
struct TYPE_10__ {TYPE_1__* dd_pool; } ;
struct TYPE_8__ {int /*<<< orphan*/ * dp_meta_objset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DD_FIELD_SNAPSHOT_COUNT ; 
 int DS_FLAG_CI_DATASET ; 
 int ENOTSUP ; 
 int MT_NORMALIZE ; 
 TYPE_6__* dsl_dataset_phys (TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_dir_snap_cmtime_update (TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_fs_ss_count_adjust (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zap_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int zap_remove_norm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *) ; 

int
dsl_dataset_snap_remove(dsl_dataset_t *ds, const char *name, dmu_tx_t *tx,
    boolean_t adj_cnt)
{
	objset_t *mos = ds->ds_dir->dd_pool->dp_meta_objset;
	uint64_t snapobj = dsl_dataset_phys(ds)->ds_snapnames_zapobj;
	matchtype_t mt = 0;
	int err;

	dsl_dir_snap_cmtime_update(ds->ds_dir);

	if (dsl_dataset_phys(ds)->ds_flags & DS_FLAG_CI_DATASET)
		mt = MT_NORMALIZE;

	err = zap_remove_norm(mos, snapobj, name, mt, tx);
	if (err == ENOTSUP && (mt & MT_NORMALIZE))
		err = zap_remove(mos, snapobj, name, tx);

	if (err == 0 && adj_cnt)
		dsl_fs_ss_count_adjust(ds->ds_dir, -1,
		    DD_FIELD_SNAPSHOT_COUNT, tx);

	return (err);
}