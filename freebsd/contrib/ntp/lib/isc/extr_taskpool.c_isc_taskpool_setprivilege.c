#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int ntasks; int /*<<< orphan*/ ** tasks; } ;
typedef  TYPE_1__ isc_taskpool_t ;
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_task_setprivilege (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
isc_taskpool_setprivilege(isc_taskpool_t *pool, isc_boolean_t priv) {
	unsigned int i;

	REQUIRE(pool != NULL);

	for (i = 0; i < pool->ntasks; i++) {
		if (pool->tasks[i] != NULL)
			isc_task_setprivilege(pool->tasks[i], priv);
	}
}