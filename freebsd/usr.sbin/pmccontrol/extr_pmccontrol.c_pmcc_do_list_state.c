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
typedef  int u_long ;
struct pmc_pmcinfo {struct pmc_info* pm_pmcs; } ;
struct pmc_info {char* pm_name; int pm_ownerpid; int /*<<< orphan*/  pm_reloadcount; int /*<<< orphan*/  pm_mode; int /*<<< orphan*/  pm_event; int /*<<< orphan*/  pm_rowdisp; scalar_t__ pm_enabled; int /*<<< orphan*/  pm_class; } ;
struct pmc_cpuinfo {int pm_ncpu; scalar_t__ pm_cputype; int pm_npmc; } ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 scalar_t__ CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ ENXIO ; 
 int /*<<< orphan*/  EX_OSERR ; 
 scalar_t__ PMC_CPU_INTEL_PIV ; 
 scalar_t__ PMC_IS_SAMPLING_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _SC_CPUSET_SIZE ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (struct pmc_pmcinfo*) ; 
 scalar_t__ pmc_cpuinfo (struct pmc_cpuinfo const**) ; 
 char* pmc_name_of_class (int /*<<< orphan*/ ) ; 
 char* pmc_name_of_cputype (scalar_t__) ; 
 char* pmc_name_of_disposition (int /*<<< orphan*/ ) ; 
 char* pmc_name_of_event (int /*<<< orphan*/ ) ; 
 int pmc_npmc (int) ; 
 scalar_t__ pmc_pmcinfo (int,struct pmc_pmcinfo**) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 long sysconf (int /*<<< orphan*/ ) ; 
 scalar_t__ sysctlbyname (char*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pmcc_do_list_state(void)
{
	cpuset_t logical_cpus_mask;
	long cpusetsize;
	size_t setsize;
	int c, cpu, n, npmc, ncpu;
	struct pmc_info *pd;
	struct pmc_pmcinfo *pi;
	const struct pmc_cpuinfo *pc;

	if (pmc_cpuinfo(&pc) != 0)
		err(EX_OSERR, "Unable to determine CPU information");

	printf("%d %s CPUs present, with %d PMCs per CPU\n", pc->pm_ncpu, 
	       pmc_name_of_cputype(pc->pm_cputype),
		pc->pm_npmc);

	/* Determine the set of logical CPUs. */
	cpusetsize = sysconf(_SC_CPUSET_SIZE);
	if (cpusetsize == -1 || (u_long)cpusetsize > sizeof(cpuset_t))
		err(EX_OSERR, "Cannot determine which CPUs are logical");
	CPU_ZERO(&logical_cpus_mask);
	setsize = (size_t)cpusetsize;
	if (sysctlbyname("machdep.logical_cpus_mask", &logical_cpus_mask,
	    &setsize, NULL, 0) < 0)
		CPU_ZERO(&logical_cpus_mask);

	ncpu = pc->pm_ncpu;

	for (c = cpu = 0; cpu < ncpu; cpu++) {
#if	defined(__i386__) || defined(__amd64__)
		if (pc->pm_cputype == PMC_CPU_INTEL_PIV &&
		    CPU_ISSET(cpu, &logical_cpus_mask))
			continue; /* skip P4-style 'logical' cpus */
#endif
		if (pmc_pmcinfo(cpu, &pi) < 0) {
			if (errno == ENXIO)
				continue;
			err(EX_OSERR, "Unable to get PMC status for CPU %d",
			    cpu);
		}

		printf("#CPU %d:\n", c++);
		npmc = pmc_npmc(cpu);
		printf("#N  NAME             CLASS  STATE    ROW-DISP\n");

		for (n = 0; n < npmc; n++) {
			pd = &pi->pm_pmcs[n];

			printf(" %-2d %-16s %-6s %-8s %-10s",
			    n,
			    pd->pm_name,
			    pmc_name_of_class(pd->pm_class),
			    pd->pm_enabled ? "ENABLED" : "DISABLED",
			    pmc_name_of_disposition(pd->pm_rowdisp));

			if (pd->pm_ownerpid != -1) {
			        printf(" (pid %d)", pd->pm_ownerpid);
				printf(" %-32s",
				    pmc_name_of_event(pd->pm_event));
				if (PMC_IS_SAMPLING_MODE(pd->pm_mode))
					printf(" (reload count %jd)",
					    pd->pm_reloadcount);
			}
			printf("\n");
		}
		free(pi);
	}
	return 0;
}