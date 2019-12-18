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
struct TYPE_11__ {int /*<<< orphan*/  vdev_mg; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_12__ {int /*<<< orphan*/  spa_name; TYPE_1__* spa_vdev_removal; } ;
typedef  TYPE_3__ spa_t ;
struct TYPE_10__ {int /*<<< orphan*/  svr_vdev_id; } ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int SCL_ALLOC ; 
 int SCL_VDEV ; 
 int /*<<< orphan*/  ZFS_SPACE_CHECK_EXTRA_RESERVED ; 
 int dsl_sync_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metaslab_group_activate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_vdev_remove_cancel_check ; 
 int /*<<< orphan*/  spa_vdev_remove_cancel_sync ; 
 int /*<<< orphan*/  spa_vdev_remove_suspend (TYPE_3__*) ; 
 TYPE_2__* vdev_lookup_top (TYPE_3__*,int /*<<< orphan*/ ) ; 

int
spa_vdev_remove_cancel(spa_t *spa)
{
	spa_vdev_remove_suspend(spa);

	if (spa->spa_vdev_removal == NULL)
		return (ESRCH);

	uint64_t vdid = spa->spa_vdev_removal->svr_vdev_id;

	int error = dsl_sync_task(spa->spa_name, spa_vdev_remove_cancel_check,
	    spa_vdev_remove_cancel_sync, NULL, 0,
	    ZFS_SPACE_CHECK_EXTRA_RESERVED);

	if (error == 0) {
		spa_config_enter(spa, SCL_ALLOC | SCL_VDEV, FTAG, RW_WRITER);
		vdev_t *vd = vdev_lookup_top(spa, vdid);
		metaslab_group_activate(vd->vdev_mg);
		spa_config_exit(spa, SCL_ALLOC | SCL_VDEV, FTAG);
	}

	return (error);
}