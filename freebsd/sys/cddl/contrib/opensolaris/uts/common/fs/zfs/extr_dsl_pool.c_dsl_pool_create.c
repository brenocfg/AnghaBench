#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_17__ {int /*<<< orphan*/  dp_config_rwlock; int /*<<< orphan*/ * dp_spa; int /*<<< orphan*/ * dp_root_dir; void* dp_meta_objset; int /*<<< orphan*/  dp_free_bpobj; int /*<<< orphan*/  dp_free_dir; int /*<<< orphan*/  dp_mos_dir; int /*<<< orphan*/  dp_root_dir_obj; int /*<<< orphan*/  dp_meta_rootbp; } ;
typedef  TYPE_1__ dsl_pool_t ;
struct TYPE_18__ {int /*<<< orphan*/  ds_bp_rwlock; } ;
typedef  TYPE_2__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int) ; 
 int /*<<< orphan*/  DMU_OST_META ; 
 int /*<<< orphan*/  DMU_OST_ZFS ; 
 int /*<<< orphan*/  DMU_OT_NONE ; 
 int /*<<< orphan*/  DMU_OT_OBJECT_DIRECTORY ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int /*<<< orphan*/  DMU_POOL_FREE_BPOBJ ; 
 int /*<<< orphan*/ * FREE_DIR_NAME ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/ * MOS_DIR_NAME ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SPA_OLD_MAXBLOCKSIZE ; 
 scalar_t__ SPA_VERSION_DEADLISTS ; 
 scalar_t__ SPA_VERSION_DSL_SCRUB ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpobj_alloc (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpobj_open (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 void* dmu_objset_create_impl (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create_assigned (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_create_sync_dd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dsl_dataset_get_blkptr (TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_dataset_hold_obj (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dir_create_sync (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_hold_obj (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_pool_create_origin (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* dsl_pool_open_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_open_special_dir (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_scan_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcred ; 
 int /*<<< orphan*/  rrw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrw_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_version (int /*<<< orphan*/ *) ; 
 scalar_t__ zap_add (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zap_create_claim (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_create_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

dsl_pool_t *
dsl_pool_create(spa_t *spa, nvlist_t *zplprops, uint64_t txg)
{
	int err;
	dsl_pool_t *dp = dsl_pool_open_impl(spa, txg);
	dmu_tx_t *tx = dmu_tx_create_assigned(dp, txg);
	dsl_dataset_t *ds;
	uint64_t obj;

	rrw_enter(&dp->dp_config_rwlock, RW_WRITER, FTAG);

	/* create and open the MOS (meta-objset) */
	dp->dp_meta_objset = dmu_objset_create_impl(spa,
	    NULL, &dp->dp_meta_rootbp, DMU_OST_META, tx);

	/* create the pool directory */
	err = zap_create_claim(dp->dp_meta_objset, DMU_POOL_DIRECTORY_OBJECT,
	    DMU_OT_OBJECT_DIRECTORY, DMU_OT_NONE, 0, tx);
	ASSERT0(err);

	/* Initialize scan structures */
	VERIFY0(dsl_scan_init(dp, txg));

	/* create and open the root dir */
	dp->dp_root_dir_obj = dsl_dir_create_sync(dp, NULL, NULL, tx);
	VERIFY0(dsl_dir_hold_obj(dp, dp->dp_root_dir_obj,
	    NULL, dp, &dp->dp_root_dir));

	/* create and open the meta-objset dir */
	(void) dsl_dir_create_sync(dp, dp->dp_root_dir, MOS_DIR_NAME, tx);
	VERIFY0(dsl_pool_open_special_dir(dp,
	    MOS_DIR_NAME, &dp->dp_mos_dir));

	if (spa_version(spa) >= SPA_VERSION_DEADLISTS) {
		/* create and open the free dir */
		(void) dsl_dir_create_sync(dp, dp->dp_root_dir,
		    FREE_DIR_NAME, tx);
		VERIFY0(dsl_pool_open_special_dir(dp,
		    FREE_DIR_NAME, &dp->dp_free_dir));

		/* create and open the free_bplist */
		obj = bpobj_alloc(dp->dp_meta_objset, SPA_OLD_MAXBLOCKSIZE, tx);
		VERIFY(zap_add(dp->dp_meta_objset, DMU_POOL_DIRECTORY_OBJECT,
		    DMU_POOL_FREE_BPOBJ, sizeof (uint64_t), 1, &obj, tx) == 0);
		VERIFY0(bpobj_open(&dp->dp_free_bpobj,
		    dp->dp_meta_objset, obj));
	}

	if (spa_version(spa) >= SPA_VERSION_DSL_SCRUB)
		dsl_pool_create_origin(dp, tx);

	/* create the root dataset */
	obj = dsl_dataset_create_sync_dd(dp->dp_root_dir, NULL, 0, tx);

	/* create the root objset */
	VERIFY0(dsl_dataset_hold_obj(dp, obj, FTAG, &ds));
#ifdef _KERNEL
	{
		objset_t *os;
		rrw_enter(&ds->ds_bp_rwlock, RW_READER, FTAG);
		os = dmu_objset_create_impl(dp->dp_spa, ds,
		    dsl_dataset_get_blkptr(ds), DMU_OST_ZFS, tx);
		rrw_exit(&ds->ds_bp_rwlock, FTAG);
		zfs_create_fs(os, kcred, zplprops, tx);
	}
#endif
	dsl_dataset_rele(ds, FTAG);

	dmu_tx_commit(tx);

	rrw_exit(&dp->dp_config_rwlock, FTAG);

	return (dp);
}