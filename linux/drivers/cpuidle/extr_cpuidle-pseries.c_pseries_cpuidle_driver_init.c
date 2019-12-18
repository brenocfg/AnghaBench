#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpuidle_driver {size_t state_count; TYPE_1__* states; } ;
struct TYPE_2__ {int /*<<< orphan*/ * enter; } ;

/* Variables and functions */
 TYPE_1__* cpuidle_state_table ; 
 int max_idle_state ; 
 struct cpuidle_driver pseries_idle_driver ; 

__attribute__((used)) static int pseries_cpuidle_driver_init(void)
{
	int idle_state;
	struct cpuidle_driver *drv = &pseries_idle_driver;

	drv->state_count = 0;

	for (idle_state = 0; idle_state < max_idle_state; ++idle_state) {
		/* Is the state not enabled? */
		if (cpuidle_state_table[idle_state].enter == NULL)
			continue;

		drv->states[drv->state_count] =	/* structure copy */
			cpuidle_state_table[idle_state];

		drv->state_count += 1;
	}

	return 0;
}