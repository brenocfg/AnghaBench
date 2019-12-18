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
struct hi6220_clk_divider {unsigned int shift; int /*<<< orphan*/  width; int /*<<< orphan*/  table; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_DIVIDER_ROUND_CLOSEST ; 
 unsigned int div_mask (int /*<<< orphan*/ ) ; 
 unsigned long divider_recalc_rate (struct clk_hw*,unsigned long,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int readl_relaxed (int /*<<< orphan*/ ) ; 
 struct hi6220_clk_divider* to_hi6220_clk_divider (struct clk_hw*) ; 

__attribute__((used)) static unsigned long hi6220_clkdiv_recalc_rate(struct clk_hw *hw,
					unsigned long parent_rate)
{
	unsigned int val;
	struct hi6220_clk_divider *dclk = to_hi6220_clk_divider(hw);

	val = readl_relaxed(dclk->reg) >> dclk->shift;
	val &= div_mask(dclk->width);

	return divider_recalc_rate(hw, parent_rate, val, dclk->table,
				   CLK_DIVIDER_ROUND_CLOSEST, dclk->width);
}