#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_4__* vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  vdev_initializing_state_t ;
struct TYPE_6__ {scalar_t__ spa_sync_on; } ;

/* Variables and functions */
 int /*<<< orphan*/  spa_get_dsl (TYPE_4__*) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_initialize_stop_all_impl (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
vdev_initialize_stop_all(vdev_t *vd, vdev_initializing_state_t tgt_state)
{
	vdev_initialize_stop_all_impl(vd, tgt_state);

	if (vd->vdev_spa->spa_sync_on) {
		/* Make sure that our state has been synced to disk */
		txg_wait_synced(spa_get_dsl(vd->vdev_spa), 0);
	}
}