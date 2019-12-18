#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int vdev_id; int vdev_children; TYPE_2__* vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int uint64_t ;
struct TYPE_14__ {TYPE_1__* spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RW_WRITER ; 
 scalar_t__ SCL_ALL ; 
 scalar_t__ spa_config_held (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  vdev_add_child (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* vdev_alloc_common (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_compact_children (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_config_dirty (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_hole_ops ; 
 int /*<<< orphan*/  vdev_reopen (TYPE_1__*) ; 

__attribute__((used)) static void
vdev_remove_make_hole_and_free(vdev_t *vd)
{
	uint64_t id = vd->vdev_id;
	spa_t *spa = vd->vdev_spa;
	vdev_t *rvd = spa->spa_root_vdev;
	boolean_t last_vdev = (id == (rvd->vdev_children - 1));

	ASSERT(MUTEX_HELD(&spa_namespace_lock));
	ASSERT(spa_config_held(spa, SCL_ALL, RW_WRITER) == SCL_ALL);

	vdev_free(vd);

	if (last_vdev) {
		vdev_compact_children(rvd);
	} else {
		vd = vdev_alloc_common(spa, id, 0, &vdev_hole_ops);
		vdev_add_child(rvd, vd);
	}
	vdev_config_dirty(rvd);

	/*
	 * Reassess the health of our root vdev.
	 */
	vdev_reopen(rvd);
}