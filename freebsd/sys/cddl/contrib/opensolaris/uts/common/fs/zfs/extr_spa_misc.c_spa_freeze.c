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
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {scalar_t__ spa_freeze_txg; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_ALL ; 
 scalar_t__ TXG_SIZE ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_get_dsl (TYPE_1__*) ; 
 scalar_t__ spa_last_synced_txg (TYPE_1__*) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,scalar_t__) ; 

void
spa_freeze(spa_t *spa)
{
	uint64_t freeze_txg = 0;

	spa_config_enter(spa, SCL_ALL, FTAG, RW_WRITER);
	if (spa->spa_freeze_txg == UINT64_MAX) {
		freeze_txg = spa_last_synced_txg(spa) + TXG_SIZE;
		spa->spa_freeze_txg = freeze_txg;
	}
	spa_config_exit(spa, SCL_ALL, FTAG);
	if (freeze_txg != 0)
		txg_wait_synced(spa_get_dsl(spa), freeze_txg);
}