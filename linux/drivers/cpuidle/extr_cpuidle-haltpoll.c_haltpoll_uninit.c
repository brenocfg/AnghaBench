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

/* Variables and functions */
 int /*<<< orphan*/  cpuhp_remove_state (scalar_t__) ; 
 int /*<<< orphan*/  cpuidle_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * haltpoll_cpuidle_devices ; 
 int /*<<< orphan*/  haltpoll_driver ; 
 scalar_t__ haltpoll_hp_state ; 

__attribute__((used)) static void haltpoll_uninit(void)
{
	if (haltpoll_hp_state)
		cpuhp_remove_state(haltpoll_hp_state);
	cpuidle_unregister_driver(&haltpoll_driver);

	free_percpu(haltpoll_cpuidle_devices);
	haltpoll_cpuidle_devices = NULL;
}