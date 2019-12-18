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
 int /*<<< orphan*/  CIU_REG (int) ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pm_scu_clk_disable(void)
{
	unsigned int val;

	/* close AXI fabric clock gate */
	__raw_writel(0x0, CIU_REG(0x64));
	__raw_writel(0x0, CIU_REG(0x68));

	/* close MCB master clock gate */
	val = __raw_readl(CIU_REG(0x1c));
	val |= 0xf0;
	__raw_writel(val, CIU_REG(0x1c));

	return ;
}