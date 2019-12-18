#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  spa_dsl_pool; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  DS_FIND_CHILDREN ; 
 int dmu_objset_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_name (TYPE_1__*) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zil_reset ; 

int
spa_reset_logs(spa_t *spa)
{
	int error;

	error = dmu_objset_find(spa_name(spa), zil_reset,
	    NULL, DS_FIND_CHILDREN);
	if (error == 0) {
		/*
		 * We successfully offlined the log device, sync out the
		 * current txg so that the "stubby" block can be removed
		 * by zil_sync().
		 */
		txg_wait_synced(spa->spa_dsl_pool, 0);
	}
	return (error);
}