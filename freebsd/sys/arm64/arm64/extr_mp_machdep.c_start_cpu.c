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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t u_int ;
struct pcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPCPU_SIZE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 size_t MAXCPU ; 
 int MP_QUIRK_CPULIST ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int PSCI_MISSING ; 
 int PSCI_RETVAL_SUCCESS ; 
 struct pcpu* __pcpu ; 
 int /*<<< orphan*/  all_cpus ; 
 size_t cpu0 ; 
 int /*<<< orphan*/ ** dpcpu ; 
 int /*<<< orphan*/  dpcpu_init (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kmem_malloc (int /*<<< orphan*/ ,int) ; 
 size_t mp_maxid ; 
 int /*<<< orphan*/  mp_ncpus ; 
 int mp_quirks ; 
 scalar_t__ mpentry ; 
 int /*<<< orphan*/  pcpu_destroy (struct pcpu*) ; 
 int /*<<< orphan*/  pcpu_init (struct pcpu*,size_t,int) ; 
 int /*<<< orphan*/  pmap_extract (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,size_t,int /*<<< orphan*/ ) ; 
 int psci_cpu_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static bool
start_cpu(u_int id, uint64_t target_cpu)
{
	struct pcpu *pcpup;
	vm_paddr_t pa;
	u_int cpuid;
	int err;

	/* Check we are able to start this cpu */
	if (id > mp_maxid)
		return (false);

	KASSERT(id < MAXCPU, ("Too many CPUs"));

	/* We are already running on cpu 0 */
	if (id == cpu0)
		return (true);

	/*
	 * Rotate the CPU IDs to put the boot CPU as CPU 0. We keep the other
	 * CPUs ordered as the are likely grouped into clusters so it can be
	 * useful to keep that property, e.g. for the GICv3 driver to send
	 * an IPI to all CPUs in the cluster.
	 */
	cpuid = id;
	if (cpuid < cpu0)
		cpuid += mp_maxid + 1;
	cpuid -= cpu0;

	pcpup = &__pcpu[cpuid];
	pcpu_init(pcpup, cpuid, sizeof(struct pcpu));

	dpcpu[cpuid - 1] = (void *)kmem_malloc(DPCPU_SIZE, M_WAITOK | M_ZERO);
	dpcpu_init(dpcpu[cpuid - 1], cpuid);

	printf("Starting CPU %u (%lx)\n", cpuid, target_cpu);
	pa = pmap_extract(kernel_pmap, (vm_offset_t)mpentry);

	err = psci_cpu_on(target_cpu, pa, cpuid);
	if (err != PSCI_RETVAL_SUCCESS) {
		/*
		 * Panic here if INVARIANTS are enabled and PSCI failed to
		 * start the requested CPU. If psci_cpu_on returns PSCI_MISSING
		 * to indicate we are unable to use it to start the given CPU.
		 */
		KASSERT(err == PSCI_MISSING ||
		    (mp_quirks & MP_QUIRK_CPULIST) == MP_QUIRK_CPULIST,
		    ("Failed to start CPU %u (%lx)\n", id, target_cpu));

		pcpu_destroy(pcpup);
		kmem_free((vm_offset_t)dpcpu[cpuid - 1], DPCPU_SIZE);
		dpcpu[cpuid - 1] = NULL;
		mp_ncpus--;

		/* Notify the user that the CPU failed to start */
		printf("Failed to start CPU %u (%lx)\n", id, target_cpu);
	} else
		CPU_SET(cpuid, &all_cpus);

	return (true);
}