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
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dir_t ;
struct TYPE_5__ {int /*<<< orphan*/  ds_is_snapshot; } ;
typedef  TYPE_1__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_6__ {int /*<<< orphan*/  doca_origin; int /*<<< orphan*/  doca_cred; int /*<<< orphan*/  doca_clone; } ;
typedef  TYPE_2__ dmu_objset_clone_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  EDQUOT ; 
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_PROP_FILESYSTEM_LIMIT ; 
 int /*<<< orphan*/ * dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int dsl_dataset_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int dsl_dir_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,char const**) ; 
 int /*<<< orphan*/  dsl_dir_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dsl_fs_ss_limit_check (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ ,char) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dmu_objset_clone_check(void *arg, dmu_tx_t *tx)
{
	dmu_objset_clone_arg_t *doca = arg;
	dsl_dir_t *pdd;
	const char *tail;
	int error;
	dsl_dataset_t *origin;
	dsl_pool_t *dp = dmu_tx_pool(tx);

	if (strchr(doca->doca_clone, '@') != NULL)
		return (SET_ERROR(EINVAL));

	if (strlen(doca->doca_clone) >= ZFS_MAX_DATASET_NAME_LEN)
		return (SET_ERROR(ENAMETOOLONG));

	error = dsl_dir_hold(dp, doca->doca_clone, FTAG, &pdd, &tail);
	if (error != 0)
		return (error);
	if (tail == NULL) {
		dsl_dir_rele(pdd, FTAG);
		return (SET_ERROR(EEXIST));
	}

	error = dsl_fs_ss_limit_check(pdd, 1, ZFS_PROP_FILESYSTEM_LIMIT, NULL,
	    doca->doca_cred);
	if (error != 0) {
		dsl_dir_rele(pdd, FTAG);
		return (SET_ERROR(EDQUOT));
	}
	dsl_dir_rele(pdd, FTAG);

	error = dsl_dataset_hold(dp, doca->doca_origin, FTAG, &origin);
	if (error != 0)
		return (error);

	/* You can only clone snapshots, not the head datasets. */
	if (!origin->ds_is_snapshot) {
		dsl_dataset_rele(origin, FTAG);
		return (SET_ERROR(EINVAL));
	}
	dsl_dataset_rele(origin, FTAG);

	return (0);
}