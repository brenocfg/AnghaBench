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
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  HIP01_BOOT_ADDRESS ; 
 scalar_t__ REG_SC_CTRL ; 
 unsigned int SC_SCTL_REMAP_CLR ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __pa_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  barrier () ; 
 scalar_t__ ctrl_base ; 
 int /*<<< orphan*/  hip01_set_boot_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hip01_set_cpu (unsigned int,int) ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 unsigned int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  secondary_startup ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

__attribute__((used)) static int hip01_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	phys_addr_t jumpaddr;
	unsigned int remap_reg_value = 0;
	struct device_node *node;


	jumpaddr = __pa_symbol(secondary_startup);
	hip01_set_boot_addr(HIP01_BOOT_ADDRESS, jumpaddr);

	node = of_find_compatible_node(NULL, NULL, "hisilicon,hip01-sysctrl");
	if (WARN_ON(!node))
		return -1;
	ctrl_base = of_iomap(node, 0);

	/* set the secondary core boot from DDR */
	remap_reg_value = readl_relaxed(ctrl_base + REG_SC_CTRL);
	barrier();
	remap_reg_value |= SC_SCTL_REMAP_CLR;
	barrier();
	writel_relaxed(remap_reg_value, ctrl_base + REG_SC_CTRL);

	hip01_set_cpu(cpu, true);

	return 0;
}