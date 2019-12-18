#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_9__ {int /*<<< orphan*/  ms_activation_weight; int /*<<< orphan*/  ms_weight; TYPE_2__* ms_group; } ;
typedef  TYPE_3__ metaslab_t ;
struct TYPE_8__ {TYPE_1__* mg_vd; } ;
struct TYPE_7__ {int /*<<< orphan*/ * vdev_spa; } ;

/* Variables and functions */
 int WEIGHT_GET_INDEX (int /*<<< orphan*/ ) ; 
 scalar_t__ WEIGHT_IS_SPACEBASED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metaslab_passivate (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metaslab_weight_from_range_tree (TYPE_3__*) ; 
 int spa_sync_pass (int /*<<< orphan*/ *) ; 
 int zfs_metaslab_switch_threshold ; 

void
metaslab_segment_may_passivate(metaslab_t *msp)
{
	spa_t *spa = msp->ms_group->mg_vd->vdev_spa;

	if (WEIGHT_IS_SPACEBASED(msp->ms_weight) || spa_sync_pass(spa) > 1)
		return;

	/*
	 * Since we are in the middle of a sync pass, the most accurate
	 * information that is accessible to us is the in-core range tree
	 * histogram; calculate the new weight based on that information.
	 */
	uint64_t weight = metaslab_weight_from_range_tree(msp);
	int activation_idx = WEIGHT_GET_INDEX(msp->ms_activation_weight);
	int current_idx = WEIGHT_GET_INDEX(weight);

	if (current_idx <= activation_idx - zfs_metaslab_switch_threshold)
		metaslab_passivate(msp, weight);
}