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
struct cpuidle_device {scalar_t__ registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_haltpoll_disable (unsigned int) ; 
 int /*<<< orphan*/  cpuidle_unregister_device (struct cpuidle_device*) ; 
 int /*<<< orphan*/  haltpoll_cpuidle_devices ; 
 struct cpuidle_device* per_cpu_ptr (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int haltpoll_cpu_offline(unsigned int cpu)
{
	struct cpuidle_device *dev;

	dev = per_cpu_ptr(haltpoll_cpuidle_devices, cpu);
	if (dev->registered) {
		arch_haltpoll_disable(cpu);
		cpuidle_unregister_device(dev);
	}

	return 0;
}