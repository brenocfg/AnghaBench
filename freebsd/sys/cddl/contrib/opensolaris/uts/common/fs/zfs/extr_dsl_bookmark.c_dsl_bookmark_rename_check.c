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
typedef  int /*<<< orphan*/  zfs_bookmark_phys_t ;
struct TYPE_9__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_1__ dsl_pool_t ;
struct TYPE_10__ {scalar_t__ ds_is_snapshot; } ;
typedef  TYPE_2__ dsl_dataset_t ;
struct TYPE_11__ {int /*<<< orphan*/  dbra_newname; int /*<<< orphan*/  dbra_oldname; int /*<<< orphan*/  dbra_fsname; } ;
typedef  TYPE_3__ dsl_bookmark_rename_arg_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int ESRCH ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_FEATURE_BOOKMARKS ; 
 scalar_t__ ZFS_MAX_DATASET_NAME_LEN ; 
 TYPE_1__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int dsl_dataset_bmark_lookup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dsl_dataset_hold (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_feature_is_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_component_namecheck (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dsl_bookmark_rename_check(void *arg, dmu_tx_t *tx)
{
	dsl_bookmark_rename_arg_t *dbra = arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	dsl_dataset_t *ds;
	zfs_bookmark_phys_t bmark_phys;
	int error;

	if (!spa_feature_is_enabled(dp->dp_spa, SPA_FEATURE_BOOKMARKS))
		return (SET_ERROR(ENOTSUP));

	/* Check validity and the full length of the new bookmark name. */
	if (zfs_component_namecheck(dbra->dbra_newname, NULL, NULL))
		return (SET_ERROR(EINVAL));
	if (strlen(dbra->dbra_fsname) + strlen(dbra->dbra_newname) + 1 >=
	    ZFS_MAX_DATASET_NAME_LEN)
		return (SET_ERROR(ENAMETOOLONG));

	error = dsl_dataset_hold(dp, dbra->dbra_fsname, FTAG, &ds);
	if (error != 0)
		return (error);
	if (ds->ds_is_snapshot) {
		dsl_dataset_rele(ds, FTAG);
		return (SET_ERROR(EINVAL));
	}
	error = dsl_dataset_bmark_lookup(ds, dbra->dbra_oldname, &bmark_phys);
	if (error != 0) {
		dsl_dataset_rele(ds, FTAG);
		return (error);
	}

	error = dsl_dataset_bmark_lookup(ds, dbra->dbra_newname, &bmark_phys);
	dsl_dataset_rele(ds, FTAG);
	if (error == 0)
		return (SET_ERROR(EEXIST));
	if (error != ESRCH)
		return (error);
	return (0);
}