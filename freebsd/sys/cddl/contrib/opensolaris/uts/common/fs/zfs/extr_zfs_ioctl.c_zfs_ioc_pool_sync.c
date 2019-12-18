#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  spa_root_vdev; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_CONFIG ; 
 scalar_t__ fnvlist_lookup_boolean_value (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  spa_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_get_dsl (TYPE_1__*) ; 
 int spa_open (char const*,TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_config_dirty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_ioc_pool_sync(const char *pool, nvlist_t *innvl, nvlist_t *onvl)
{
	int err;
	boolean_t force;
	spa_t *spa;

	if ((err = spa_open(pool, &spa, FTAG)) != 0)
		return (err);

	force = fnvlist_lookup_boolean_value(innvl, "force");
	if (force) {
		spa_config_enter(spa, SCL_CONFIG, FTAG, RW_WRITER);
		vdev_config_dirty(spa->spa_root_vdev);
		spa_config_exit(spa, SCL_CONFIG, FTAG);
	}
	txg_wait_synced(spa_get_dsl(spa), 0);

	spa_close(spa, FTAG);

	return (err);
}