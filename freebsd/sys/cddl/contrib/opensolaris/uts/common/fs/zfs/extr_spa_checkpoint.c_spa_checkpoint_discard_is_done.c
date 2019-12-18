#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t vdev_children; TYPE_2__** vdev_child; } ;
typedef  TYPE_3__ vdev_t ;
typedef  size_t uint64_t ;
struct TYPE_11__ {TYPE_3__* spa_root_vdev; } ;
typedef  TYPE_4__ spa_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_8__ {int /*<<< orphan*/  vs_checkpoint_space; } ;
struct TYPE_9__ {TYPE_1__ vdev_stat; int /*<<< orphan*/ * vdev_checkpoint_sm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  SPA_FEATURE_POOL_CHECKPOINT ; 
 int spa_feature_is_active (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_has_checkpoint (TYPE_4__*) ; 

__attribute__((used)) static boolean_t
spa_checkpoint_discard_is_done(spa_t *spa)
{
	vdev_t *rvd = spa->spa_root_vdev;

	ASSERT(!spa_has_checkpoint(spa));
	ASSERT(spa_feature_is_active(spa, SPA_FEATURE_POOL_CHECKPOINT));

	for (uint64_t c = 0; c < rvd->vdev_children; c++) {
		if (rvd->vdev_child[c]->vdev_checkpoint_sm != NULL)
			return (B_FALSE);
		ASSERT0(rvd->vdev_child[c]->vdev_stat.vs_checkpoint_space);
	}

	return (B_TRUE);
}