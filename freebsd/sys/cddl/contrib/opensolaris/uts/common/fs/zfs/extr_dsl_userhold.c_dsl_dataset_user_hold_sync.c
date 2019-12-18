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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_5__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_1__ dsl_pool_t ;
struct TYPE_6__ {scalar_t__ dduha_minor; int /*<<< orphan*/  dduha_chkholds; } ;
typedef  TYPE_2__ dsl_dataset_user_hold_arg_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 TYPE_1__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_hold (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_user_hold_sync_one_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_onexit_hold_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvpair_value_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gethrestime_sec () ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dsl_dataset_user_hold_sync(void *arg, dmu_tx_t *tx)
{
	dsl_dataset_user_hold_arg_t *dduha = arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	nvlist_t *tmpholds;
	uint64_t now = gethrestime_sec();

	if (dduha->dduha_minor != 0)
		tmpholds = fnvlist_alloc();
	else
		tmpholds = NULL;
	for (nvpair_t *pair = nvlist_next_nvpair(dduha->dduha_chkholds, NULL);
	    pair != NULL;
	    pair = nvlist_next_nvpair(dduha->dduha_chkholds, pair)) {
		dsl_dataset_t *ds;

		VERIFY0(dsl_dataset_hold(dp, nvpair_name(pair), FTAG, &ds));
		dsl_dataset_user_hold_sync_one_impl(tmpholds, ds,
		    fnvpair_value_string(pair), dduha->dduha_minor, now, tx);
		dsl_dataset_rele(ds, FTAG);
	}
	dsl_onexit_hold_cleanup(dp->dp_spa, tmpholds, dduha->dduha_minor);
}