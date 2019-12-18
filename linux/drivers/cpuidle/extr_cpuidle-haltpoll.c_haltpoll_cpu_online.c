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
struct cpuidle_device {unsigned int cpu; int /*<<< orphan*/  registered; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  arch_haltpoll_enable (unsigned int) ; 
 scalar_t__ cpuidle_register_device (struct cpuidle_device*) ; 
 int /*<<< orphan*/  haltpoll_cpuidle_devices ; 
 struct cpuidle_device* per_cpu_ptr (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_notice (char*,unsigned int) ; 

__attribute__((used)) static int haltpoll_cpu_online(unsigned int cpu)
{
	struct cpuidle_device *dev;

	dev = per_cpu_ptr(haltpoll_cpuidle_devices, cpu);
	if (!dev->registered) {
		dev->cpu = cpu;
		if (cpuidle_register_device(dev)) {
			pr_notice("cpuidle_register_device %d failed!\n", cpu);
			return -EIO;
		}
		arch_haltpoll_enable(cpu);
	}

	return 0;
}