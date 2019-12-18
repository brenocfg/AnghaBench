#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  spa_scrub_reopen; int /*<<< orphan*/  spa_root_vdev; } ;
typedef  TYPE_1__ spa_t ;
typedef  scalar_t__ pool_scan_func_t ;
struct TYPE_11__ {int /*<<< orphan*/  scn_dp; } ;
typedef  TYPE_2__ dsl_scan_t ;
struct TYPE_12__ {TYPE_2__* dp_scan; TYPE_1__* dp_spa; } ;
typedef  TYPE_3__ dsl_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int ECANCELED ; 
 int /*<<< orphan*/  ESC_ZFS_SCRUB_RESUME ; 
 scalar_t__ POOL_SCAN_SCRUB ; 
 int /*<<< orphan*/  POOL_SCRUB_NORMAL ; 
 int /*<<< orphan*/  SCL_NONE ; 
 int SET_ERROR (int) ; 
 int /*<<< orphan*/  ZFS_SPACE_CHECK_EXTRA_RESERVED ; 
 scalar_t__ dsl_scan_is_paused_scrub (TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_scan_setup_check ; 
 int /*<<< orphan*/  dsl_scan_setup_sync ; 
 int dsl_scrub_set_pause_resume (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dsl_sync_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_event_notify (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_name (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_vdev_state_enter (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_vdev_state_exit (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_reopen (int /*<<< orphan*/ ) ; 

int
dsl_scan(dsl_pool_t *dp, pool_scan_func_t func)
{
	spa_t *spa = dp->dp_spa;
	dsl_scan_t *scn = dp->dp_scan;

	/*
	 * Purge all vdev caches and probe all devices.  We do this here
	 * rather than in sync context because this requires a writer lock
	 * on the spa_config lock, which we can't do from sync context.  The
	 * spa_scrub_reopen flag indicates that vdev_open() should not
	 * attempt to start another scrub.
	 */
	spa_vdev_state_enter(spa, SCL_NONE);
	spa->spa_scrub_reopen = B_TRUE;
	vdev_reopen(spa->spa_root_vdev);
	spa->spa_scrub_reopen = B_FALSE;
	(void) spa_vdev_state_exit(spa, NULL, 0);

	if (func == POOL_SCAN_SCRUB && dsl_scan_is_paused_scrub(scn)) {
		/* got scrub start cmd, resume paused scrub */
		int err = dsl_scrub_set_pause_resume(scn->scn_dp,
		    POOL_SCRUB_NORMAL);
		if (err == 0) {
			spa_event_notify(spa, NULL, NULL, ESC_ZFS_SCRUB_RESUME);
			return (ECANCELED);
		}
		return (SET_ERROR(err));
	}

	return (dsl_sync_task(spa_name(spa), dsl_scan_setup_check,
	    dsl_scan_setup_sync, &func, 0, ZFS_SPACE_CHECK_EXTRA_RESERVED));
}