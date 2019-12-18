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
struct TYPE_7__ {int /*<<< orphan*/  vdev_state_dirty_node; TYPE_2__* vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;
struct TYPE_8__ {int /*<<< orphan*/  spa_state_dirty_list; } ;
typedef  TYPE_2__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_STATE ; 
 scalar_t__ dsl_pool_sync_context (int /*<<< orphan*/ ) ; 
 int list_link_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ spa_config_held (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_get_dsl (TYPE_2__*) ; 

void
vdev_state_clean(vdev_t *vd)
{
	spa_t *spa = vd->vdev_spa;

	ASSERT(spa_config_held(spa, SCL_STATE, RW_WRITER) ||
	    (dsl_pool_sync_context(spa_get_dsl(spa)) &&
	    spa_config_held(spa, SCL_STATE, RW_READER)));

	ASSERT(list_link_active(&vd->vdev_state_dirty_node));
	list_remove(&spa->spa_state_dirty_list, vd);
}