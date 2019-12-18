#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int (* x86_32_early_logical_apicid ) (int) ;} ;

/* Variables and functions */
 int BAD_APICID ; 
 int EINVAL ; 
 int ENODEV ; 
 int allocate_logical_cpuid (int) ; 
 TYPE_1__* apic ; 
 int boot_cpu_apic_version ; 
 int boot_cpu_physical_apicid ; 
 int* cpuid_to_apicid ; 
 int disabled_cpu_apicid ; 
 int disabled_cpus ; 
 int early_per_cpu (int /*<<< orphan*/ ,int) ; 
 int max_physical_apicid ; 
 int nr_cpu_ids ; 
 int num_processors ; 
 int /*<<< orphan*/  phys_cpu_present_map ; 
 int physid_isset (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  physid_set (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*,int,int,...) ; 
 int read_apic_id () ; 
 int /*<<< orphan*/  set_cpu_possible (int,int) ; 
 int /*<<< orphan*/  set_cpu_present (int,int) ; 
 int stub1 (int) ; 
 int /*<<< orphan*/  x86_bios_cpu_apicid ; 
 int /*<<< orphan*/  x86_cpu_to_apicid ; 
 int /*<<< orphan*/  x86_cpu_to_logical_apicid ; 

int generic_processor_info(int apicid, int version)
{
	int cpu, max = nr_cpu_ids;
	bool boot_cpu_detected = physid_isset(boot_cpu_physical_apicid,
				phys_cpu_present_map);

	/*
	 * boot_cpu_physical_apicid is designed to have the apicid
	 * returned by read_apic_id(), i.e, the apicid of the
	 * currently booting-up processor. However, on some platforms,
	 * it is temporarily modified by the apicid reported as BSP
	 * through MP table. Concretely:
	 *
	 * - arch/x86/kernel/mpparse.c: MP_processor_info()
	 * - arch/x86/mm/amdtopology.c: amd_numa_init()
	 *
	 * This function is executed with the modified
	 * boot_cpu_physical_apicid. So, disabled_cpu_apicid kernel
	 * parameter doesn't work to disable APs on kdump 2nd kernel.
	 *
	 * Since fixing handling of boot_cpu_physical_apicid requires
	 * another discussion and tests on each platform, we leave it
	 * for now and here we use read_apic_id() directly in this
	 * function, generic_processor_info().
	 */
	if (disabled_cpu_apicid != BAD_APICID &&
	    disabled_cpu_apicid != read_apic_id() &&
	    disabled_cpu_apicid == apicid) {
		int thiscpu = num_processors + disabled_cpus;

		pr_warning("APIC: Disabling requested cpu."
			   " Processor %d/0x%x ignored.\n",
			   thiscpu, apicid);

		disabled_cpus++;
		return -ENODEV;
	}

	/*
	 * If boot cpu has not been detected yet, then only allow upto
	 * nr_cpu_ids - 1 processors and keep one slot free for boot cpu
	 */
	if (!boot_cpu_detected && num_processors >= nr_cpu_ids - 1 &&
	    apicid != boot_cpu_physical_apicid) {
		int thiscpu = max + disabled_cpus - 1;

		pr_warning(
			"APIC: NR_CPUS/possible_cpus limit of %i almost"
			" reached. Keeping one slot for boot cpu."
			"  Processor %d/0x%x ignored.\n", max, thiscpu, apicid);

		disabled_cpus++;
		return -ENODEV;
	}

	if (num_processors >= nr_cpu_ids) {
		int thiscpu = max + disabled_cpus;

		pr_warning("APIC: NR_CPUS/possible_cpus limit of %i "
			   "reached. Processor %d/0x%x ignored.\n",
			   max, thiscpu, apicid);

		disabled_cpus++;
		return -EINVAL;
	}

	if (apicid == boot_cpu_physical_apicid) {
		/*
		 * x86_bios_cpu_apicid is required to have processors listed
		 * in same order as logical cpu numbers. Hence the first
		 * entry is BSP, and so on.
		 * boot_cpu_init() already hold bit 0 in cpu_present_mask
		 * for BSP.
		 */
		cpu = 0;

		/* Logical cpuid 0 is reserved for BSP. */
		cpuid_to_apicid[0] = apicid;
	} else {
		cpu = allocate_logical_cpuid(apicid);
		if (cpu < 0) {
			disabled_cpus++;
			return -EINVAL;
		}
	}

	/*
	 * Validate version
	 */
	if (version == 0x0) {
		pr_warning("BIOS bug: APIC version is 0 for CPU %d/0x%x, fixing up to 0x10\n",
			   cpu, apicid);
		version = 0x10;
	}

	if (version != boot_cpu_apic_version) {
		pr_warning("BIOS bug: APIC version mismatch, boot CPU: %x, CPU %d: version %x\n",
			boot_cpu_apic_version, cpu, version);
	}

	if (apicid > max_physical_apicid)
		max_physical_apicid = apicid;

#if defined(CONFIG_SMP) || defined(CONFIG_X86_64)
	early_per_cpu(x86_cpu_to_apicid, cpu) = apicid;
	early_per_cpu(x86_bios_cpu_apicid, cpu) = apicid;
#endif
#ifdef CONFIG_X86_32
	early_per_cpu(x86_cpu_to_logical_apicid, cpu) =
		apic->x86_32_early_logical_apicid(cpu);
#endif
	set_cpu_possible(cpu, true);
	physid_set(apicid, phys_cpu_present_map);
	set_cpu_present(cpu, true);
	num_processors++;

	return cpu;
}