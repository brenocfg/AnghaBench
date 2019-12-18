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
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CLR (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_EMPTY (int /*<<< orphan*/ *) ; 
 int CPU_FFS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int MAXCPU ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  all_cpus ; 
 int /*<<< orphan*/  ap_boot_mtx ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_cpu_mask (int /*<<< orphan*/ *) ; 
 int platform_processor_id () ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int start_ap (int) ; 

void
cpu_mp_start(void)
{
	int error, cpuid;
	cpuset_t cpumask;

	mtx_init(&ap_boot_mtx, "ap boot", NULL, MTX_SPIN);

	CPU_ZERO(&all_cpus);
	platform_cpu_mask(&cpumask);

	while (!CPU_EMPTY(&cpumask)) {
		cpuid = CPU_FFS(&cpumask) - 1;
		CPU_CLR(cpuid, &cpumask);

		if (cpuid >= MAXCPU) {
			printf("cpu_mp_start: ignoring AP #%d.\n", cpuid);
			continue;
		}

		if (cpuid != platform_processor_id()) {
			if ((error = start_ap(cpuid)) != 0) {
				printf("AP #%d failed to start: %d\n", cpuid, error);
				continue;
			}
			if (bootverbose)
				printf("AP #%d started!\n", cpuid);
		}
		CPU_SET(cpuid, &all_cpus);
	}
}