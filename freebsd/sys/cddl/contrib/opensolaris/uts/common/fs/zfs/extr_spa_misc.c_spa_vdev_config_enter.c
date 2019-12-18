#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_ALL ; 
 int /*<<< orphan*/  spa_config_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_last_synced_txg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 

uint64_t
spa_vdev_config_enter(spa_t *spa)
{
	ASSERT(MUTEX_HELD(&spa_namespace_lock));

	spa_config_enter(spa, SCL_ALL, spa, RW_WRITER);

	return (spa_last_synced_txg(spa) + 1);
}