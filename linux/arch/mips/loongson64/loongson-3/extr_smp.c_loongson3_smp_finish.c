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
 int HZ ; 
 size_t cpu_logical_map (int) ; 
 scalar_t__* ipi_mailbox_buf ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  loongson3_ipi_write64 (int /*<<< orphan*/ ,scalar_t__) ; 
 int mips_hpt_frequency ; 
 int /*<<< orphan*/  pr_info (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ read_c0_count () ; 
 int /*<<< orphan*/  read_c0_status () ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  write_c0_compare (scalar_t__) ; 

__attribute__((used)) static void loongson3_smp_finish(void)
{
	int cpu = smp_processor_id();

	write_c0_compare(read_c0_count() + mips_hpt_frequency/HZ);
	local_irq_enable();
	loongson3_ipi_write64(0,
			ipi_mailbox_buf[cpu_logical_map(cpu)] + 0x0);
	pr_info("CPU#%d finished, CP0_ST=%x\n",
			smp_processor_id(), read_c0_status());
}