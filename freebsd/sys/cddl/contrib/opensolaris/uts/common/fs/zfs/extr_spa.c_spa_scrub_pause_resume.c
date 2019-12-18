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
typedef  int /*<<< orphan*/  pool_scrub_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_ALL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ dsl_scan_resilvering (int /*<<< orphan*/ ) ; 
 int dsl_scrub_set_pause_resume (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_config_held (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
spa_scrub_pause_resume(spa_t *spa, pool_scrub_cmd_t cmd)
{
	ASSERT(spa_config_held(spa, SCL_ALL, RW_WRITER) == 0);

	if (dsl_scan_resilvering(spa->spa_dsl_pool))
		return (SET_ERROR(EBUSY));

	return (dsl_scrub_set_pause_resume(spa->spa_dsl_pool, cmd));
}