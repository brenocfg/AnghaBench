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
struct clk_hw {int dummy; } ;
struct clk_divider {unsigned int shift; int /*<<< orphan*/  flags; int /*<<< orphan*/  reg; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 unsigned int PCG_DIV_SHIFT ; 
 int /*<<< orphan*/  PCG_DIV_WIDTH ; 
 unsigned int clk_div_mask (int /*<<< orphan*/ ) ; 
 unsigned long divider_recalc_rate (struct clk_hw*,unsigned long,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 struct clk_divider* to_clk_divider (struct clk_hw*) ; 

__attribute__((used)) static unsigned long imx8m_clk_composite_divider_recalc_rate(struct clk_hw *hw,
						unsigned long parent_rate)
{
	struct clk_divider *divider = to_clk_divider(hw);
	unsigned long prediv_rate;
	unsigned int prediv_value;
	unsigned int div_value;

	prediv_value = readl(divider->reg) >> divider->shift;
	prediv_value &= clk_div_mask(divider->width);

	prediv_rate = divider_recalc_rate(hw, parent_rate, prediv_value,
						NULL, divider->flags,
						divider->width);

	div_value = readl(divider->reg) >> PCG_DIV_SHIFT;
	div_value &= clk_div_mask(PCG_DIV_WIDTH);

	return divider_recalc_rate(hw, prediv_rate, div_value, NULL,
				   divider->flags, PCG_DIV_WIDTH);
}