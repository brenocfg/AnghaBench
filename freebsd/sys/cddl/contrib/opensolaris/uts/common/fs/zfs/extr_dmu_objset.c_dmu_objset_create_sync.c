#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_13__ {TYPE_8__* dd_pool; } ;
typedef  TYPE_1__ dsl_dir_t ;
struct TYPE_14__ {int /*<<< orphan*/  ds_bp_rwlock; } ;
typedef  TYPE_2__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_15__ {int /*<<< orphan*/  doca_cred; int /*<<< orphan*/  doca_userarg; int /*<<< orphan*/  (* doca_userfunc ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  doca_type; int /*<<< orphan*/  doca_flags; int /*<<< orphan*/  doca_name; } ;
typedef  TYPE_3__ dmu_objset_create_arg_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
struct TYPE_16__ {int /*<<< orphan*/  dp_spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dmu_objset_create_impl (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_create_sync (TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dsl_dataset_get_blkptr (TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_dataset_hold_obj (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dir_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**,char const**) ; 
 int /*<<< orphan*/  dsl_dir_rele (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrw_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_history_log_internal_ds (TYPE_2__*,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dmu_objset_create_sync(void *arg, dmu_tx_t *tx)
{
	dmu_objset_create_arg_t *doca = arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	dsl_dir_t *pdd;
	const char *tail;
	dsl_dataset_t *ds;
	uint64_t obj;
	blkptr_t *bp;
	objset_t *os;

	VERIFY0(dsl_dir_hold(dp, doca->doca_name, FTAG, &pdd, &tail));

	obj = dsl_dataset_create_sync(pdd, tail, NULL, doca->doca_flags,
	    doca->doca_cred, tx);

	VERIFY0(dsl_dataset_hold_obj(pdd->dd_pool, obj, FTAG, &ds));
	rrw_enter(&ds->ds_bp_rwlock, RW_READER, FTAG);
	bp = dsl_dataset_get_blkptr(ds);
	os = dmu_objset_create_impl(pdd->dd_pool->dp_spa,
	    ds, bp, doca->doca_type, tx);
	rrw_exit(&ds->ds_bp_rwlock, FTAG);

	if (doca->doca_userfunc != NULL) {
		doca->doca_userfunc(os, doca->doca_userarg,
		    doca->doca_cred, tx);
	}

	spa_history_log_internal_ds(ds, "create", tx, "");
	dsl_dataset_rele(ds, FTAG);
	dsl_dir_rele(pdd, FTAG);
}