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
 int /*<<< orphan*/  CPU_CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CPU_CMP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_NAND (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  all_cpus ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  shutdown_cpus ; 
 int /*<<< orphan*/  stop_cpus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stopped_cpus ; 

void
cpu_mp_shutdown(void)
{
	cpuset_t cpus;
	int i;

	critical_enter();
	shutdown_cpus = all_cpus;
	CPU_CLR(PCPU_GET(cpuid), &shutdown_cpus);
	cpus = shutdown_cpus;

	/* XXX: Stop all the CPUs which aren't already. */
	if (CPU_CMP(&stopped_cpus, &cpus)) {

		/* cpus is just a flat "on" mask without curcpu. */
		CPU_NAND(&cpus, &stopped_cpus);
		stop_cpus(cpus);
	}
	i = 0;
	while (!CPU_EMPTY(&shutdown_cpus)) {
		if (i++ > 100000) {
			printf("timeout shutting down CPUs.\n");
			break;
		}
	}
	critical_exit();
}