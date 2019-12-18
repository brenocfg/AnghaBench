#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int vdev_reopening; int /*<<< orphan*/ * vdev_aux; int /*<<< orphan*/  vdev_offline; TYPE_2__* vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;
struct TYPE_16__ {int /*<<< orphan*/  spa_l2cache; } ;
typedef  TYPE_2__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  RW_WRITER ; 
 scalar_t__ SCL_STATE_ALL ; 
 int /*<<< orphan*/  l2arc_add_vdev (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  l2arc_vdev_present (TYPE_1__*) ; 
 scalar_t__ spa_config_held (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_close (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_open (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_propagate_state (TYPE_1__*) ; 
 scalar_t__ vdev_readable (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_validate (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_validate_aux (TYPE_1__*) ; 
 scalar_t__ vdev_writeable (TYPE_1__*) ; 

void
vdev_reopen(vdev_t *vd)
{
	spa_t *spa = vd->vdev_spa;

	ASSERT(spa_config_held(spa, SCL_STATE_ALL, RW_WRITER) == SCL_STATE_ALL);

	/* set the reopening flag unless we're taking the vdev offline */
	vd->vdev_reopening = !vd->vdev_offline;
	vdev_close(vd);
	(void) vdev_open(vd);

	/*
	 * Call vdev_validate() here to make sure we have the same device.
	 * Otherwise, a device with an invalid label could be successfully
	 * opened in response to vdev_reopen().
	 */
	if (vd->vdev_aux) {
		(void) vdev_validate_aux(vd);
		if (vdev_readable(vd) && vdev_writeable(vd) &&
		    vd->vdev_aux == &spa->spa_l2cache &&
		    !l2arc_vdev_present(vd))
			l2arc_add_vdev(spa, vd);
	} else {
		(void) vdev_validate(vd);
	}

	/*
	 * Reassess parent vdev's health.
	 */
	vdev_propagate_state(vd);
}