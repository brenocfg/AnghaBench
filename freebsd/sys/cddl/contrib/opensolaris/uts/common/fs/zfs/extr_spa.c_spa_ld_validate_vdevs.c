#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ vdev_state; } ;
typedef  TYPE_1__ vdev_t ;
struct TYPE_10__ {TYPE_1__* spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_ALL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ VDEV_STATE_CANT_OPEN ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_load_failed (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  vdev_dbgmsg_print_tree (TYPE_1__*,int) ; 
 int vdev_validate (TYPE_1__*) ; 

__attribute__((used)) static int
spa_ld_validate_vdevs(spa_t *spa)
{
	int error = 0;
	vdev_t *rvd = spa->spa_root_vdev;

	spa_config_enter(spa, SCL_ALL, FTAG, RW_WRITER);
	error = vdev_validate(rvd);
	spa_config_exit(spa, SCL_ALL, FTAG);

	if (error != 0) {
		spa_load_failed(spa, "vdev_validate failed [error=%d]", error);
		return (error);
	}

	if (rvd->vdev_state <= VDEV_STATE_CANT_OPEN) {
		spa_load_failed(spa, "cannot open vdev tree after invalidating "
		    "some vdevs");
		vdev_dbgmsg_print_tree(rvd, 2);
		return (SET_ERROR(ENXIO));
	}

	return (0);
}