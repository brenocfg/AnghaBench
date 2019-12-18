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
typedef  scalar_t__ u32 ;
struct nlm_soc_info {int coremask; int /*<<< orphan*/  picbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOT_CPU_READY ; 
 unsigned int NLM_THREADS_PER_CORE ; 
 unsigned int NR_CPUS ; 
 int /*<<< orphan*/  cpumask_test_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 unsigned int hard_smp_processor_id () ; 
 unsigned int nlm_cores_per_node () ; 
 int /*<<< orphan*/  nlm_cpumask ; 
 scalar_t__* nlm_get_boot_data (int /*<<< orphan*/ ) ; 
 struct nlm_soc_info* nlm_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_pic_send_ipi (int /*<<< orphan*/ ,unsigned int,int,int) ; 
 int /*<<< orphan*/  nlm_rmiboot_preboot ; 
 int /*<<< orphan*/  nlm_set_nmi_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int xlr_wakeup_secondary_cpus(void)
{
	struct nlm_soc_info *nodep;
	unsigned int i, j, boot_cpu;
	volatile u32 *cpu_ready = nlm_get_boot_data(BOOT_CPU_READY);

	/*
	 *  In case of RMI boot, hit with NMI to get the cores
	 *  from bootloader to linux code.
	 */
	nodep = nlm_get_node(0);
	boot_cpu = hard_smp_processor_id();
	nlm_set_nmi_handler(nlm_rmiboot_preboot);
	for (i = 0; i < NR_CPUS; i++) {
		if (i == boot_cpu || !cpumask_test_cpu(i, &nlm_cpumask))
			continue;
		nlm_pic_send_ipi(nodep->picbase, i, 1, 1); /* send NMI */
	}

	/* Fill up the coremask early */
	nodep->coremask = 1;
	for (i = 1; i < nlm_cores_per_node(); i++) {
		for (j = 1000000; j > 0; j--) {
			if (cpu_ready[i * NLM_THREADS_PER_CORE])
				break;
			udelay(10);
		}
		if (j != 0)
			nodep->coremask |= (1u << i);
		else
			pr_err("Failed to wakeup core %d\n", i);
	}

	return 0;
}