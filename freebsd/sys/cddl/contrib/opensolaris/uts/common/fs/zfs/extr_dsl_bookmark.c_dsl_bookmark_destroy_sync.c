#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
struct TYPE_10__ {int /*<<< orphan*/  dp_spa; int /*<<< orphan*/ * dp_meta_objset; } ;
typedef  TYPE_1__ dsl_pool_t ;
struct TYPE_11__ {int /*<<< orphan*/  ds_object; scalar_t__ ds_bookmarks; int /*<<< orphan*/  ds_dbuf; } ;
typedef  TYPE_2__ dsl_dataset_t ;
struct TYPE_12__ {int /*<<< orphan*/  dbda_success; } ;
typedef  TYPE_3__ dsl_bookmark_destroy_arg_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  DS_FIELD_BOOKMARK_NAMES ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  SPA_FEATURE_BOOKMARKS ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_bookmark_hold_ds (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  dsl_dataset_bookmark_remove (TYPE_2__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_feature_decr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_history_log_internal_ds (TYPE_2__*,char*,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  zap_count (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  zap_destroy (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dsl_bookmark_destroy_sync(void *arg, dmu_tx_t *tx)
{
	dsl_bookmark_destroy_arg_t *dbda = arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	objset_t *mos = dp->dp_meta_objset;

	for (nvpair_t *pair = nvlist_next_nvpair(dbda->dbda_success, NULL);
	    pair != NULL; pair = nvlist_next_nvpair(dbda->dbda_success, pair)) {
		dsl_dataset_t *ds;
		char *shortname;
		uint64_t zap_cnt;

		VERIFY0(dsl_bookmark_hold_ds(dp, nvpair_name(pair),
		    &ds, FTAG, &shortname));
		VERIFY0(dsl_dataset_bookmark_remove(ds, shortname, tx));

		/*
		 * If all of this dataset's bookmarks have been destroyed,
		 * free the zap object and decrement the feature's use count.
		 */
		VERIFY0(zap_count(mos, ds->ds_bookmarks,
		    &zap_cnt));
		if (zap_cnt == 0) {
			dmu_buf_will_dirty(ds->ds_dbuf, tx);
			VERIFY0(zap_destroy(mos, ds->ds_bookmarks, tx));
			ds->ds_bookmarks = 0;
			spa_feature_decr(dp->dp_spa, SPA_FEATURE_BOOKMARKS, tx);
			VERIFY0(zap_remove(mos, ds->ds_object,
			    DS_FIELD_BOOKMARK_NAMES, tx));
		}

		spa_history_log_internal_ds(ds, "remove bookmark", tx,
		    "name=%s", shortname);

		dsl_dataset_rele(ds, FTAG);
	}
}