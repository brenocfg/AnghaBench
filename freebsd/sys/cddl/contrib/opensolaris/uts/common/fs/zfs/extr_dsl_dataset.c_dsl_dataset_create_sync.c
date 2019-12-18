#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_13__ {int /*<<< orphan*/ * dp_meta_objset; int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_1__ dsl_pool_t ;
struct TYPE_14__ {int /*<<< orphan*/  dd_object; TYPE_1__* dd_pool; } ;
typedef  TYPE_2__ dsl_dir_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  int /*<<< orphan*/  cnt ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DD_FIELD_FILESYSTEM_COUNT ; 
 int /*<<< orphan*/  DD_FIELD_SNAPSHOT_COUNT ; 
 int DS_CREATE_FLAG_NODIRTY ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  SPA_FEATURE_FS_SS_LIMIT ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int dmu_tx_is_syncing (int /*<<< orphan*/ *) ; 
 int dsl_dataset_create_sync_dd (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_hold_obj (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_zero_zil (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_deleg_set_create_perms (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dsl_dir_create_sync (TYPE_1__*,TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_hold_obj (TYPE_1__*,int,char const*,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  dsl_dir_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dir_zapify (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ spa_feature_is_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*,int /*<<< orphan*/ *) ; 

uint64_t
dsl_dataset_create_sync(dsl_dir_t *pdd, const char *lastname,
    dsl_dataset_t *origin, uint64_t flags, cred_t *cr, dmu_tx_t *tx)
{
	dsl_pool_t *dp = pdd->dd_pool;
	uint64_t dsobj, ddobj;
	dsl_dir_t *dd;

	ASSERT(dmu_tx_is_syncing(tx));
	ASSERT(lastname[0] != '@');

	ddobj = dsl_dir_create_sync(dp, pdd, lastname, tx);
	VERIFY0(dsl_dir_hold_obj(dp, ddobj, lastname, FTAG, &dd));

	dsobj = dsl_dataset_create_sync_dd(dd, origin,
	    flags & ~DS_CREATE_FLAG_NODIRTY, tx);

	dsl_deleg_set_create_perms(dd, tx, cr);

	/*
	 * Since we're creating a new node we know it's a leaf, so we can
	 * initialize the counts if the limit feature is active.
	 */
	if (spa_feature_is_active(dp->dp_spa, SPA_FEATURE_FS_SS_LIMIT)) {
		uint64_t cnt = 0;
		objset_t *os = dd->dd_pool->dp_meta_objset;

		dsl_dir_zapify(dd, tx);
		VERIFY0(zap_add(os, dd->dd_object, DD_FIELD_FILESYSTEM_COUNT,
		    sizeof (cnt), 1, &cnt, tx));
		VERIFY0(zap_add(os, dd->dd_object, DD_FIELD_SNAPSHOT_COUNT,
		    sizeof (cnt), 1, &cnt, tx));
	}

	dsl_dir_rele(dd, FTAG);

	/*
	 * If we are creating a clone, make sure we zero out any stale
	 * data from the origin snapshots zil header.
	 */
	if (origin != NULL && !(flags & DS_CREATE_FLAG_NODIRTY)) {
		dsl_dataset_t *ds;

		VERIFY0(dsl_dataset_hold_obj(dp, dsobj, FTAG, &ds));
		dsl_dataset_zero_zil(ds, tx);
		dsl_dataset_rele(ds, FTAG);
	}

	return (dsobj);
}