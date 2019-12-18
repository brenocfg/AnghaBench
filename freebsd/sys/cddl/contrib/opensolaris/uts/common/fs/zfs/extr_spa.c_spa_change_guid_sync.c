#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  vdev_guid_sum; scalar_t__ vdev_guid; } ;
typedef  TYPE_1__ vdev_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_10__ {TYPE_1__* spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_11__ {TYPE_2__* dp_spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_STATE ; 
 TYPE_8__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_guid (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_history_log_internal (TYPE_2__*,char*,int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vdev_config_dirty (TYPE_1__*) ; 

__attribute__((used)) static void
spa_change_guid_sync(void *arg, dmu_tx_t *tx)
{
	uint64_t *newguid = arg;
	spa_t *spa = dmu_tx_pool(tx)->dp_spa;
	uint64_t oldguid;
	vdev_t *rvd = spa->spa_root_vdev;

	oldguid = spa_guid(spa);

	spa_config_enter(spa, SCL_STATE, FTAG, RW_READER);
	rvd->vdev_guid = *newguid;
	rvd->vdev_guid_sum += (*newguid - oldguid);
	vdev_config_dirty(rvd);
	spa_config_exit(spa, SCL_STATE, FTAG);

	spa_history_log_internal(spa, "guid change", tx, "old=%llu new=%llu",
	    oldguid, *newguid);
}