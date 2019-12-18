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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ PRCM_PWR_SWITCH_REG (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,unsigned int) ; 
 scalar_t__ prcm_base ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int sunxi_cpu_power_switch_set(unsigned int cpu, unsigned int cluster,
				      bool enable)
{
	u32 reg;

	/* control sequence from Allwinner A80 user manual v1.2 PRCM section */
	reg = readl(prcm_base + PRCM_PWR_SWITCH_REG(cluster, cpu));
	if (enable) {
		if (reg == 0x00) {
			pr_debug("power clamp for cluster %u cpu %u already open\n",
				 cluster, cpu);
			return 0;
		}

		writel(0xff, prcm_base + PRCM_PWR_SWITCH_REG(cluster, cpu));
		udelay(10);
		writel(0xfe, prcm_base + PRCM_PWR_SWITCH_REG(cluster, cpu));
		udelay(10);
		writel(0xf8, prcm_base + PRCM_PWR_SWITCH_REG(cluster, cpu));
		udelay(10);
		writel(0xf0, prcm_base + PRCM_PWR_SWITCH_REG(cluster, cpu));
		udelay(10);
		writel(0x00, prcm_base + PRCM_PWR_SWITCH_REG(cluster, cpu));
		udelay(10);
	} else {
		writel(0xff, prcm_base + PRCM_PWR_SWITCH_REG(cluster, cpu));
		udelay(10);
	}

	return 0;
}