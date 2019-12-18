#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_3__ {int /*<<< orphan*/  dp_mos_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRED () ; 
 int EINVAL ; 
 int SET_ERROR (int) ; 
 scalar_t__ SPA_VERSION_ZPOOL_HISTORY ; 
 int /*<<< orphan*/  TXG_WAIT ; 
 int /*<<< orphan*/  ZFS_SPACE_CHECK_NONE ; 
 int /*<<< orphan*/  ZPOOL_HIST_WHO ; 
 int /*<<< orphan*/  ZPOOL_HIST_ZONE ; 
 int /*<<< orphan*/  crgetruid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_abort (int /*<<< orphan*/ *) ; 
 int dmu_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create_dd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_sync_task_nowait (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_dup (int /*<<< orphan*/ *) ; 
 TYPE_1__* spa_get_dsl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_history_log_sync ; 
 int /*<<< orphan*/ * spa_history_zone () ; 
 scalar_t__ spa_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_writeable (int /*<<< orphan*/ *) ; 

int
spa_history_log_nvl(spa_t *spa, nvlist_t *nvl)
{
	int err = 0;
	dmu_tx_t *tx;
	nvlist_t *nvarg;

	if (spa_version(spa) < SPA_VERSION_ZPOOL_HISTORY)
		return (EINVAL);

	if (spa_version(spa) < SPA_VERSION_ZPOOL_HISTORY || !spa_writeable(spa))
		return (SET_ERROR(EINVAL));

	tx = dmu_tx_create_dd(spa_get_dsl(spa)->dp_mos_dir);
	err = dmu_tx_assign(tx, TXG_WAIT);
	if (err) {
		dmu_tx_abort(tx);
		return (err);
	}

	nvarg = fnvlist_dup(nvl);
	if (spa_history_zone() != NULL) {
		fnvlist_add_string(nvarg, ZPOOL_HIST_ZONE,
		    spa_history_zone());
	}
	fnvlist_add_uint64(nvarg, ZPOOL_HIST_WHO, crgetruid(CRED()));

	/* Kick this off asynchronously; errors are ignored. */
	dsl_sync_task_nowait(spa_get_dsl(spa), spa_history_log_sync,
	    nvarg, 0, ZFS_SPACE_CHECK_NONE, tx);
	dmu_tx_commit(tx);

	/* spa_history_log_sync will free nvl */
	return (err);

}