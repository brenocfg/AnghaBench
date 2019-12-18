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
 int /*<<< orphan*/  TF_SET_CPU_BOOT_ADDR_SMC ; 
 unsigned long cpu_boot_addr ; 
 int /*<<< orphan*/  tf_generic_smc (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tf_set_cpu_boot_addr(int cpu, unsigned long boot_addr)
{
	cpu_boot_addr = boot_addr;
	tf_generic_smc(TF_SET_CPU_BOOT_ADDR_SMC, cpu_boot_addr, 0);

	return 0;
}