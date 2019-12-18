#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  vdev_dtl_lock; TYPE_3__* vdev_spa; int /*<<< orphan*/ ** vdev_dtl; } ;
typedef  TYPE_1__ vdev_t ;
typedef  size_t vdev_dtl_type_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  range_tree_t ;
struct TYPE_5__ {TYPE_1__* spa_root_vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 size_t DTL_TYPES ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_tree_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_tree_contains (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spa_writeable (TYPE_3__*) ; 

void
vdev_dtl_dirty(vdev_t *vd, vdev_dtl_type_t t, uint64_t txg, uint64_t size)
{
	range_tree_t *rt = vd->vdev_dtl[t];

	ASSERT(t < DTL_TYPES);
	ASSERT(vd != vd->vdev_spa->spa_root_vdev);
	ASSERT(spa_writeable(vd->vdev_spa));

	mutex_enter(&vd->vdev_dtl_lock);
	if (!range_tree_contains(rt, txg, size))
		range_tree_add(rt, txg, size);
	mutex_exit(&vd->vdev_dtl_lock);
}