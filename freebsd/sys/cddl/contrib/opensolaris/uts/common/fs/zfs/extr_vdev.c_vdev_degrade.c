#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned long long vdev_degraded; scalar_t__ vdev_faulted; TYPE_1__* vdev_ops; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int /*<<< orphan*/  vdev_aux_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_7__ {int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  SCL_NONE ; 
 int /*<<< orphan*/  VDEV_STATE_DEGRADED ; 
 TYPE_2__* spa_lookup_by_guid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_vdev_state_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spa_vdev_state_exit (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_is_dead (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_set_state (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
vdev_degrade(spa_t *spa, uint64_t guid, vdev_aux_t aux)
{
	vdev_t *vd;

	spa_vdev_state_enter(spa, SCL_NONE);

	if ((vd = spa_lookup_by_guid(spa, guid, B_TRUE)) == NULL)
		return (spa_vdev_state_exit(spa, NULL, ENODEV));

	if (!vd->vdev_ops->vdev_op_leaf)
		return (spa_vdev_state_exit(spa, NULL, ENOTSUP));

	/*
	 * If the vdev is already faulted, then don't do anything.
	 */
	if (vd->vdev_faulted || vd->vdev_degraded)
		return (spa_vdev_state_exit(spa, NULL, 0));

	vd->vdev_degraded = 1ULL;
	if (!vdev_is_dead(vd))
		vdev_set_state(vd, B_FALSE, VDEV_STATE_DEGRADED,
		    aux);

	return (spa_vdev_state_exit(spa, vd, 0));
}