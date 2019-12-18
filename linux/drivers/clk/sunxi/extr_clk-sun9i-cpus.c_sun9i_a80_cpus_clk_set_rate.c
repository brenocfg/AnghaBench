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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sun9i_a80_cpus_clk {int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUN9I_CPUS_DIV_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN9I_CPUS_MUX_GET_PARENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN9I_CPUS_PLL4_DIV_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sun9i_a80_cpus_clk_round (unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  sun9i_a80_cpus_lock ; 
 struct sun9i_a80_cpus_clk* to_sun9i_a80_cpus_clk (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun9i_a80_cpus_clk_set_rate(struct clk_hw *hw, unsigned long rate,
				       unsigned long parent_rate)
{
	struct sun9i_a80_cpus_clk *cpus = to_sun9i_a80_cpus_clk(hw);
	unsigned long flags;
	u8 div, pre_div, parent;
	u32 reg;

	spin_lock_irqsave(&sun9i_a80_cpus_lock, flags);

	reg = readl(cpus->reg);

	/* need to know which parent is used to apply pre-divider */
	parent = SUN9I_CPUS_MUX_GET_PARENT(reg);
	sun9i_a80_cpus_clk_round(rate, &div, &pre_div, parent, parent_rate);

	reg = SUN9I_CPUS_DIV_SET(reg, div);
	reg = SUN9I_CPUS_PLL4_DIV_SET(reg, pre_div);
	writel(reg, cpus->reg);

	spin_unlock_irqrestore(&sun9i_a80_cpus_lock, flags);

	return 0;
}