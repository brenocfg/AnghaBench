#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {struct TYPE_13__* vdev_top; int /*<<< orphan*/  vdev_children; int /*<<< orphan*/  vdev_id; int /*<<< orphan*/  vdev_crtxg; int /*<<< orphan*/  vdev_state; int /*<<< orphan*/  vdev_physical_ashift; int /*<<< orphan*/  vdev_logical_ashift; int /*<<< orphan*/  vdev_ashift; int /*<<< orphan*/  vdev_psize; int /*<<< orphan*/  vdev_max_asize; int /*<<< orphan*/  vdev_min_asize; int /*<<< orphan*/  vdev_asize; struct TYPE_13__* vdev_parent; int /*<<< orphan*/ * vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  vdev_ops_t ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  RW_WRITER ; 
 scalar_t__ SCL_ALL ; 
 scalar_t__ spa_config_held (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_add_child (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* vdev_alloc_common (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_remove_child (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_top_transfer (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_top_update (TYPE_1__*,TYPE_1__*) ; 

vdev_t *
vdev_add_parent(vdev_t *cvd, vdev_ops_t *ops)
{
	spa_t *spa = cvd->vdev_spa;
	vdev_t *pvd = cvd->vdev_parent;
	vdev_t *mvd;

	ASSERT(spa_config_held(spa, SCL_ALL, RW_WRITER) == SCL_ALL);

	mvd = vdev_alloc_common(spa, cvd->vdev_id, 0, ops);

	mvd->vdev_asize = cvd->vdev_asize;
	mvd->vdev_min_asize = cvd->vdev_min_asize;
	mvd->vdev_max_asize = cvd->vdev_max_asize;
	mvd->vdev_psize = cvd->vdev_psize;
	mvd->vdev_ashift = cvd->vdev_ashift;
	mvd->vdev_logical_ashift = cvd->vdev_logical_ashift;
	mvd->vdev_physical_ashift = cvd->vdev_physical_ashift;
	mvd->vdev_state = cvd->vdev_state;
	mvd->vdev_crtxg = cvd->vdev_crtxg;

	vdev_remove_child(pvd, cvd);
	vdev_add_child(pvd, mvd);
	cvd->vdev_id = mvd->vdev_children;
	vdev_add_child(mvd, cvd);
	vdev_top_update(cvd->vdev_top, cvd->vdev_top);

	if (mvd == mvd->vdev_top)
		vdev_top_transfer(cvd, mvd);

	return (mvd);
}