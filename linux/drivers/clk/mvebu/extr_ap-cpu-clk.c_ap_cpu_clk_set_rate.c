#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct clk_hw {int dummy; } ;
struct ap_cpu_clk {unsigned int cluster; TYPE_1__* pll_regs; int /*<<< orphan*/  pll_cr_base; } ;
struct TYPE_2__ {unsigned int divider_reg; unsigned int cluster_offset; unsigned int force_reg; unsigned int ratio_reg; int divider_mask; int divider_offset; int divider_ratio; unsigned int force_mask; int ratio_state_cluster_offset; scalar_t__ ratio_offset; int /*<<< orphan*/  ratio_state_reg; scalar_t__ ratio_state_offset; } ;

/* Variables and functions */
 int AP807_PLL_CR_1_CPU_CLK_DIV_RATIO_MASK ; 
 int AP807_PLL_CR_1_CPU_CLK_DIV_RATIO_OFFSET ; 
 unsigned int BIT (scalar_t__) ; 
 int /*<<< orphan*/  STATUS_POLL_PERIOD_US ; 
 int /*<<< orphan*/  STATUS_POLL_TIMEOUT_US ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,unsigned int,int*) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,unsigned int,int) ; 
 struct ap_cpu_clk* to_ap_cpu_clk (struct clk_hw*) ; 

__attribute__((used)) static int ap_cpu_clk_set_rate(struct clk_hw *hw, unsigned long rate,
			       unsigned long parent_rate)
{
	struct ap_cpu_clk *clk = to_ap_cpu_clk(hw);
	int ret, reg, divider = parent_rate / rate;
	unsigned int cpu_clkdiv_reg, cpu_force_reg, cpu_ratio_reg, stable_bit;

	cpu_clkdiv_reg = clk->pll_regs->divider_reg +
		(clk->cluster * clk->pll_regs->cluster_offset);
	cpu_force_reg = clk->pll_regs->force_reg +
		(clk->cluster * clk->pll_regs->cluster_offset);
	cpu_ratio_reg = clk->pll_regs->ratio_reg +
		(clk->cluster * clk->pll_regs->cluster_offset);

	regmap_read(clk->pll_cr_base, cpu_clkdiv_reg, &reg);
	reg &= ~(clk->pll_regs->divider_mask);
	reg |= (divider << clk->pll_regs->divider_offset);

	/*
	 * AP807 CPU divider has two channels with ratio 1:3 and divider_ratio
	 * is 1. Otherwise, in the case of the AP806, divider_ratio is 0.
	 */
	if (clk->pll_regs->divider_ratio) {
		reg &= ~(AP807_PLL_CR_1_CPU_CLK_DIV_RATIO_MASK);
		reg |= ((divider * clk->pll_regs->divider_ratio) <<
				AP807_PLL_CR_1_CPU_CLK_DIV_RATIO_OFFSET);
	}
	regmap_write(clk->pll_cr_base, cpu_clkdiv_reg, reg);


	regmap_update_bits(clk->pll_cr_base, cpu_force_reg,
			   clk->pll_regs->force_mask,
			   clk->pll_regs->force_mask);

	regmap_update_bits(clk->pll_cr_base, cpu_ratio_reg,
			   BIT(clk->pll_regs->ratio_offset),
			   BIT(clk->pll_regs->ratio_offset));

	stable_bit = BIT(clk->pll_regs->ratio_state_offset +
			 clk->cluster *
			 clk->pll_regs->ratio_state_cluster_offset),
	ret = regmap_read_poll_timeout(clk->pll_cr_base,
				       clk->pll_regs->ratio_state_reg, reg,
				       reg & stable_bit, STATUS_POLL_PERIOD_US,
				       STATUS_POLL_TIMEOUT_US);
	if (ret)
		return ret;

	regmap_update_bits(clk->pll_cr_base, cpu_ratio_reg,
			   BIT(clk->pll_regs->ratio_offset), 0);

	return 0;
}