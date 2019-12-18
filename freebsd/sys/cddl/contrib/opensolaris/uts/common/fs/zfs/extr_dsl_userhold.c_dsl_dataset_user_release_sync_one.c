#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  longlong_t ;
struct TYPE_10__ {int /*<<< orphan*/ * dp_meta_objset; } ;
typedef  TYPE_2__ dsl_pool_t ;
struct TYPE_11__ {scalar_t__ ds_userrefs; int /*<<< orphan*/  ds_object; TYPE_1__* ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_12__ {int /*<<< orphan*/  ds_userrefs_obj; } ;
struct TYPE_9__ {TYPE_2__* dd_pool; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 TYPE_7__* dsl_dataset_phys (TYPE_3__*) ; 
 int dsl_pool_user_release (TYPE_2__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_history_log_internal_ds (TYPE_3__*,char*,int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dsl_dataset_user_release_sync_one(dsl_dataset_t *ds, nvlist_t *holds,
    dmu_tx_t *tx)
{
	dsl_pool_t *dp = ds->ds_dir->dd_pool;
	objset_t *mos = dp->dp_meta_objset;

	for (nvpair_t *pair = nvlist_next_nvpair(holds, NULL); pair != NULL;
	    pair = nvlist_next_nvpair(holds, pair)) {
		int error;
		const char *holdname = nvpair_name(pair);

		/* Remove temporary hold if one exists. */
		error = dsl_pool_user_release(dp, ds->ds_object, holdname, tx);
		VERIFY(error == 0 || error == ENOENT);

		VERIFY0(zap_remove(mos, dsl_dataset_phys(ds)->ds_userrefs_obj,
		    holdname, tx));
		ds->ds_userrefs--;

		spa_history_log_internal_ds(ds, "release", tx,
		    "tag=%s refs=%lld", holdname, (longlong_t)ds->ds_userrefs);
	}
}