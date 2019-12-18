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
struct task_struct {int dummy; } ;
struct device_node {int /*<<< orphan*/  phandle; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ callin_flag ; 
 int /*<<< orphan*/ * cpu_new_thread ; 
 scalar_t__ hypervisor ; 
 int /*<<< orphan*/  kfree (void*) ; 
 scalar_t__ ldom_domaining_enabled ; 
 int /*<<< orphan*/  ldom_startcpu_cpuid (unsigned int,unsigned long,void**) ; 
 struct device_node* of_find_node_by_cpuid (unsigned int) ; 
 int /*<<< orphan*/  printk (char*,unsigned int) ; 
 int /*<<< orphan*/  prom_startcpu (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  prom_startcpu_cpuid (unsigned int,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  sparc64_cpu_startup ; 
 int /*<<< orphan*/ * task_thread_info (struct task_struct*) ; 
 scalar_t__ tlb_type ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int smp_boot_one_cpu(unsigned int cpu, struct task_struct *idle)
{
	unsigned long entry =
		(unsigned long)(&sparc64_cpu_startup);
	unsigned long cookie =
		(unsigned long)(&cpu_new_thread);
	void *descr = NULL;
	int timeout, ret;

	callin_flag = 0;
	cpu_new_thread = task_thread_info(idle);

	if (tlb_type == hypervisor) {
#if defined(CONFIG_SUN_LDOMS) && defined(CONFIG_HOTPLUG_CPU)
		if (ldom_domaining_enabled)
			ldom_startcpu_cpuid(cpu,
					    (unsigned long) cpu_new_thread,
					    &descr);
		else
#endif
			prom_startcpu_cpuid(cpu, entry, cookie);
	} else {
		struct device_node *dp = of_find_node_by_cpuid(cpu);

		prom_startcpu(dp->phandle, entry, cookie);
	}

	for (timeout = 0; timeout < 50000; timeout++) {
		if (callin_flag)
			break;
		udelay(100);
	}

	if (callin_flag) {
		ret = 0;
	} else {
		printk("Processor %d is stuck.\n", cpu);
		ret = -ENODEV;
	}
	cpu_new_thread = NULL;

	kfree(descr);

	return ret;
}