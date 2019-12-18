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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BOOT_CPU_READY ; 
 scalar_t__* nlm_get_boot_data (int /*<<< orphan*/ ) ; 
 int nlm_threads_per_core ; 

__attribute__((used)) static int wait_for_cpus(int cpu, int bootcpu)
{
	volatile uint32_t *cpu_ready = nlm_get_boot_data(BOOT_CPU_READY);
	int i, count, notready;

	count = 0x800000;
	do {
		notready = nlm_threads_per_core;
		for (i = 0; i < nlm_threads_per_core; i++)
			if (cpu_ready[cpu + i] || (cpu + i) == bootcpu)
				--notready;
	} while (notready != 0 && --count > 0);

	return count != 0;
}