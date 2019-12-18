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
struct clk_div_table {int dummy; } ;
struct clk_alpha_pll_postdiv {int width; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_DIVIDER_POWER_OF_TWO ; 
 struct clk_div_table* clk_alpha_2bit_div_table ; 
 struct clk_div_table* clk_alpha_div_table ; 
 long divider_round_rate (struct clk_hw*,unsigned long,unsigned long*,struct clk_div_table const*,int,int /*<<< orphan*/ ) ; 
 struct clk_alpha_pll_postdiv* to_clk_alpha_pll_postdiv (struct clk_hw*) ; 

__attribute__((used)) static long
clk_alpha_pll_postdiv_round_rate(struct clk_hw *hw, unsigned long rate,
				 unsigned long *prate)
{
	struct clk_alpha_pll_postdiv *pll = to_clk_alpha_pll_postdiv(hw);
	const struct clk_div_table *table;

	if (pll->width == 2)
		table = clk_alpha_2bit_div_table;
	else
		table = clk_alpha_div_table;

	return divider_round_rate(hw, rate, prate, table,
				  pll->width, CLK_DIVIDER_POWER_OF_TWO);
}