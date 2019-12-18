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
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_8__ {scalar_t__ mg_activation_count; int /*<<< orphan*/  mg_fragmentation; TYPE_1__* mg_class; } ;
typedef  TYPE_2__ metaslab_group_t ;
struct TYPE_7__ {int /*<<< orphan*/ * mc_spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_ALLOC ; 
 int /*<<< orphan*/  metaslab_group_alloc_update (TYPE_2__*) ; 
 int /*<<< orphan*/  metaslab_group_fragmentation (TYPE_2__*) ; 
 int /*<<< orphan*/  metaslab_group_preload (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_config_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
metaslab_sync_reassess(metaslab_group_t *mg)
{
	spa_t *spa = mg->mg_class->mc_spa;

	spa_config_enter(spa, SCL_ALLOC, FTAG, RW_READER);
	metaslab_group_alloc_update(mg);
	mg->mg_fragmentation = metaslab_group_fragmentation(mg);

	/*
	 * Preload the next potential metaslabs but only on active
	 * metaslab groups. We can get into a state where the metaslab
	 * is no longer active since we dirty metaslabs as we remove a
	 * a device, thus potentially making the metaslab group eligible
	 * for preloading.
	 */
	if (mg->mg_activation_count > 0) {
		metaslab_group_preload(mg);
	}
	spa_config_exit(spa, SCL_ALLOC, FTAG);
}