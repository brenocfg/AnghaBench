#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  vs_aux; } ;
struct TYPE_10__ {int vdev_reopening; TYPE_2__ vdev_stat; int /*<<< orphan*/  vdev_state; scalar_t__ vdev_offline; int /*<<< orphan*/  vdev_prevstate; TYPE_1__* vdev_ops; struct TYPE_10__* vdev_parent; int /*<<< orphan*/ * vdev_spa; } ;
typedef  TYPE_3__ vdev_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_8__ {scalar_t__ vdev_op_leaf; int /*<<< orphan*/  (* vdev_op_close ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  RW_WRITER ; 
 scalar_t__ SCL_STATE_ALL ; 
 int /*<<< orphan*/  VDEV_AUX_NONE ; 
 int /*<<< orphan*/  VDEV_STATE_CLOSED ; 
 int /*<<< orphan*/  VDEV_STATE_OFFLINE ; 
 scalar_t__ spa_config_held (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  trim_map_destroy (TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_cache_purge (TYPE_3__*) ; 

void
vdev_close(vdev_t *vd)
{
	spa_t *spa = vd->vdev_spa;
	vdev_t *pvd = vd->vdev_parent;

	ASSERT(spa_config_held(spa, SCL_STATE_ALL, RW_WRITER) == SCL_STATE_ALL);

	/*
	 * If our parent is reopening, then we are as well, unless we are
	 * going offline.
	 */
	if (pvd != NULL && pvd->vdev_reopening)
		vd->vdev_reopening = (pvd->vdev_reopening && !vd->vdev_offline);

	vd->vdev_ops->vdev_op_close(vd);

	vdev_cache_purge(vd);

	if (vd->vdev_ops->vdev_op_leaf)
		trim_map_destroy(vd);

	/*
	 * We record the previous state before we close it, so that if we are
	 * doing a reopen(), we don't generate FMA ereports if we notice that
	 * it's still faulted.
	 */
	vd->vdev_prevstate = vd->vdev_state;

	if (vd->vdev_offline)
		vd->vdev_state = VDEV_STATE_OFFLINE;
	else
		vd->vdev_state = VDEV_STATE_CLOSED;
	vd->vdev_stat.vs_aux = VDEV_AUX_NONE;
}