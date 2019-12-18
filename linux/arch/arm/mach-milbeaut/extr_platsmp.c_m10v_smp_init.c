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
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERNEL_UNBOOT_FLAG ; 
 unsigned int M10V_MAX_CPU ; 
 unsigned int MPIDR_AFFINITY_LEVEL (unsigned int,int) ; 
 scalar_t__ m10v_smp_base ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int,unsigned int) ; 
 unsigned int read_cpuid_mpidr () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void m10v_smp_init(unsigned int max_cpus)
{
	unsigned int mpidr, cpu, cluster;
	struct device_node *np;

	np = of_find_compatible_node(NULL, NULL, "socionext,milbeaut-smp-sram");
	if (!np)
		return;

	m10v_smp_base = of_iomap(np, 0);
	if (!m10v_smp_base)
		return;

	mpidr = read_cpuid_mpidr();
	cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);
	cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);
	pr_info("MCPM boot on cpu_%u cluster_%u\n", cpu, cluster);

	for (cpu = 0; cpu < M10V_MAX_CPU; cpu++)
		writel(KERNEL_UNBOOT_FLAG, m10v_smp_base + cpu * 4);
}