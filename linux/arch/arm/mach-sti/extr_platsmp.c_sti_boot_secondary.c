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

/* Variables and functions */
 unsigned long __pa_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_strt_ptr ; 
 int /*<<< orphan*/  secondary_startup ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  sync_cache_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sti_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	unsigned long entry_pa = __pa_symbol(secondary_startup);

	/*
	 * Secondary CPU is initialised and started by a U-BOOTROM firmware.
	 * Secondary CPU is spinning and waiting for a write at cpu_strt_ptr.
	 * Writing secondary_startup address at cpu_strt_ptr makes it to
	 * jump directly to secondary_startup().
	 */
	__raw_writel(entry_pa, cpu_strt_ptr);

	/* wmb so that data is actually written before cache flush is done */
	smp_wmb();
	sync_cache_w(cpu_strt_ptr);

	return 0;
}