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
 int /*<<< orphan*/  CPUS_FDT ; 
 int /*<<< orphan*/  MAXCPU ; 
 int MIN (int,int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  cpu_check_mmu ; 
 int /*<<< orphan*/  cpu_enum_method ; 
 int mp_maxid ; 
 int mp_ncpus ; 
 int ofw_cpu_early_foreach (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
cpu_mp_setmaxid(void)
{
#ifdef FDT
	int cores;

	cores = ofw_cpu_early_foreach(cpu_check_mmu, true);
	if (cores > 0) {
		cores = MIN(cores, MAXCPU);
		if (bootverbose)
			printf("Found %d CPUs in the device tree\n", cores);
		mp_ncpus = cores;
		mp_maxid = cores - 1;
		cpu_enum_method = CPUS_FDT;
		return;
	}
#endif

	if (bootverbose)
		printf("No CPU data, limiting to 1 core\n");
	mp_ncpus = 1;
	mp_maxid = 0;
}