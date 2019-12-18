#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_6__ {int /*<<< orphan*/  ds_prev; } ;
typedef  TYPE_1__ dsl_dataset_t ;
struct TYPE_7__ {int /*<<< orphan*/ * ddsa_props; int /*<<< orphan*/  ddsa_snaps; } ;
typedef  TYPE_2__ dsl_dataset_snapshot_arg_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZPROP_SRC_LOCAL ; 
 int /*<<< orphan*/ * dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_hold (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_snapshot_sync_impl (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_props_set_sync_impl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

void
dsl_dataset_snapshot_sync(void *arg, dmu_tx_t *tx)
{
	dsl_dataset_snapshot_arg_t *ddsa = arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	nvpair_t *pair;

	for (pair = nvlist_next_nvpair(ddsa->ddsa_snaps, NULL);
	    pair != NULL; pair = nvlist_next_nvpair(ddsa->ddsa_snaps, pair)) {
		dsl_dataset_t *ds;
		char *name, *atp;
		char dsname[ZFS_MAX_DATASET_NAME_LEN];

		name = nvpair_name(pair);
		atp = strchr(name, '@');
		(void) strlcpy(dsname, name, atp - name + 1);
		VERIFY0(dsl_dataset_hold(dp, dsname, FTAG, &ds));

		dsl_dataset_snapshot_sync_impl(ds, atp + 1, tx);
		if (ddsa->ddsa_props != NULL) {
			dsl_props_set_sync_impl(ds->ds_prev,
			    ZPROP_SRC_LOCAL, ddsa->ddsa_props, tx);
		}
		dsl_dataset_rele(ds, FTAG);
	}
}