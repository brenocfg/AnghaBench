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
 int TESTS ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  bind_cpu (int) ; 
 int /*<<< orphan*/  cpu_spinwait () ; 
 int gate ; 
 int /*<<< orphan*/  rdtsc () ; 
 int /*<<< orphan*/  thread_tsc ; 

__attribute__((used)) static void *
thread_main(void *arg)
{
	int cpu, i;

	cpu = (intptr_t)arg;
	bind_cpu(cpu);
	for (i = 0; i < TESTS; i++) {
		gate = 1;
		while (gate == 1)
			cpu_spinwait();
		barrier();

		__asm __volatile("lfence");
		thread_tsc = rdtsc();

		barrier();
		gate = 3;
		while (gate == 3)
			cpu_spinwait();
	}
	return (NULL);
}