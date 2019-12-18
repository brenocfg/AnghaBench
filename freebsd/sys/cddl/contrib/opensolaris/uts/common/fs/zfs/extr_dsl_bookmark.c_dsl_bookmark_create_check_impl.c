#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_bookmark_phys_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_8__ {int /*<<< orphan*/  ds_is_snapshot; } ;
typedef  TYPE_1__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int dsl_bookmark_hold_ds (int /*<<< orphan*/ *,char const*,TYPE_1__**,int /*<<< orphan*/ ,char**) ; 
 int dsl_dataset_bmark_lookup (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_is_before (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dsl_bookmark_create_check_impl(dsl_dataset_t *snapds, const char *bookmark_name,
    dmu_tx_t *tx)
{
	dsl_pool_t *dp = dmu_tx_pool(tx);
	dsl_dataset_t *bmark_fs;
	char *shortname;
	int error;
	zfs_bookmark_phys_t bmark_phys;

	if (!snapds->ds_is_snapshot)
		return (SET_ERROR(EINVAL));

	error = dsl_bookmark_hold_ds(dp, bookmark_name,
	    &bmark_fs, FTAG, &shortname);
	if (error != 0)
		return (error);

	if (!dsl_dataset_is_before(bmark_fs, snapds, 0)) {
		dsl_dataset_rele(bmark_fs, FTAG);
		return (SET_ERROR(EINVAL));
	}

	error = dsl_dataset_bmark_lookup(bmark_fs, shortname,
	    &bmark_phys);
	dsl_dataset_rele(bmark_fs, FTAG);
	if (error == 0)
		return (SET_ERROR(EEXIST));
	if (error == ESRCH)
		return (0);
	return (error);
}