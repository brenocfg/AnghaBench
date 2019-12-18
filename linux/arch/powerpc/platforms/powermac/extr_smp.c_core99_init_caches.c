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
 int /*<<< orphan*/  CPU_FTR_L2CR ; 
 int /*<<< orphan*/  CPU_FTR_L3CR ; 
 int /*<<< orphan*/  _get_L2CR () ; 
 int /*<<< orphan*/  _get_L3CR () ; 
 int /*<<< orphan*/  _set_L2CR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _set_L3CR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core99_l2_cache ; 
 int /*<<< orphan*/  core99_l3_cache ; 
 int /*<<< orphan*/  cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int,...) ; 

__attribute__((used)) static void core99_init_caches(int cpu)
{
#ifndef CONFIG_PPC64
	if (!cpu_has_feature(CPU_FTR_L2CR))
		return;

	if (cpu == 0) {
		core99_l2_cache = _get_L2CR();
		printk("CPU0: L2CR is %lx\n", core99_l2_cache);
	} else {
		printk("CPU%d: L2CR was %lx\n", cpu, _get_L2CR());
		_set_L2CR(0);
		_set_L2CR(core99_l2_cache);
		printk("CPU%d: L2CR set to %lx\n", cpu, core99_l2_cache);
	}

	if (!cpu_has_feature(CPU_FTR_L3CR))
		return;

	if (cpu == 0){
		core99_l3_cache = _get_L3CR();
		printk("CPU0: L3CR is %lx\n", core99_l3_cache);
	} else {
		printk("CPU%d: L3CR was %lx\n", cpu, _get_L3CR());
		_set_L3CR(0);
		_set_L3CR(core99_l3_cache);
		printk("CPU%d: L3CR set to %lx\n", cpu, core99_l3_cache);
	}
#endif /* !CONFIG_PPC64 */
}