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
typedef  unsigned int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  PM_CLK_GATE_REG ; 
 unsigned int PM_CLK_GATE_REG_MASK ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,int /*<<< orphan*/ ) ; 

void cns3xxx_pwr_clk_dis(unsigned int block)
{
	u32 reg = __raw_readl(PM_CLK_GATE_REG);

	reg &= ~(block & PM_CLK_GATE_REG_MASK);
	__raw_writel(reg, PM_CLK_GATE_REG);
}