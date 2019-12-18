#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nvpair_t ;
struct TYPE_5__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_1__ dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
struct TYPE_6__ {int /*<<< orphan*/  dbca_errors; int /*<<< orphan*/  dbca_bmarks; } ;
typedef  TYPE_2__ dsl_bookmark_create_arg_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_FEATURE_BOOKMARKS ; 
 TYPE_1__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int dsl_bookmark_create_check_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dsl_dataset_hold (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_int32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fnvpair_value_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_feature_is_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dsl_bookmark_create_check(void *arg, dmu_tx_t *tx)
{
	dsl_bookmark_create_arg_t *dbca = arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	int rv = 0;

	if (!spa_feature_is_enabled(dp->dp_spa, SPA_FEATURE_BOOKMARKS))
		return (SET_ERROR(ENOTSUP));

	for (nvpair_t *pair = nvlist_next_nvpair(dbca->dbca_bmarks, NULL);
	    pair != NULL; pair = nvlist_next_nvpair(dbca->dbca_bmarks, pair)) {
		dsl_dataset_t *snapds;
		int error;

		/* note: validity of nvlist checked by ioctl layer */
		error = dsl_dataset_hold(dp, fnvpair_value_string(pair),
		    FTAG, &snapds);
		if (error == 0) {
			error = dsl_bookmark_create_check_impl(snapds,
			    nvpair_name(pair), tx);
			dsl_dataset_rele(snapds, FTAG);
		}
		if (error != 0) {
			fnvlist_add_int32(dbca->dbca_errors,
			    nvpair_name(pair), error);
			rv = error;
		}
	}

	return (rv);
}