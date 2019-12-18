#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  dp_meta_objset; int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_1__ dsl_pool_t ;
struct TYPE_10__ {int /*<<< orphan*/  dd_object; } ;
typedef  TYPE_2__ dsl_dir_t ;
struct TYPE_11__ {TYPE_2__* ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  DD_FIELD_FILESYSTEM_COUNT ; 
 int /*<<< orphan*/  EALREADY ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_FEATURE_FS_SS_LIMIT ; 
 TYPE_1__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int dsl_dataset_hold (TYPE_1__*,char*,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dsl_dir_is_zapified (TYPE_2__*) ; 
 scalar_t__ spa_feature_is_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_feature_is_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zap_contains (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dsl_dir_actv_fs_ss_limit_check(void *arg, dmu_tx_t *tx)
{
	char *ddname = (char *)arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	dsl_dataset_t *ds;
	dsl_dir_t *dd;
	int error;

	error = dsl_dataset_hold(dp, ddname, FTAG, &ds);
	if (error != 0)
		return (error);

	if (!spa_feature_is_enabled(dp->dp_spa, SPA_FEATURE_FS_SS_LIMIT)) {
		dsl_dataset_rele(ds, FTAG);
		return (SET_ERROR(ENOTSUP));
	}

	dd = ds->ds_dir;
	if (spa_feature_is_active(dp->dp_spa, SPA_FEATURE_FS_SS_LIMIT) &&
	    dsl_dir_is_zapified(dd) &&
	    zap_contains(dp->dp_meta_objset, dd->dd_object,
	    DD_FIELD_FILESYSTEM_COUNT) == 0) {
		dsl_dataset_rele(ds, FTAG);
		return (SET_ERROR(EALREADY));
	}

	dsl_dataset_rele(ds, FTAG);
	return (0);
}