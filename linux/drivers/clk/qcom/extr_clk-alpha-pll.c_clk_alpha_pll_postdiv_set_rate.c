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
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct clk_alpha_pll_postdiv {TYPE_1__ clkr; } ;

/* Variables and functions */
 int DIV_ROUND_UP_ULL (unsigned long,unsigned long) ; 
 int PLL_POST_DIV_MASK (struct clk_alpha_pll_postdiv*) ; 
 int PLL_POST_DIV_SHIFT ; 
 int /*<<< orphan*/  PLL_USER_CTL (struct clk_alpha_pll_postdiv*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct clk_alpha_pll_postdiv* to_clk_alpha_pll_postdiv (struct clk_hw*) ; 

__attribute__((used)) static int clk_alpha_pll_postdiv_set_rate(struct clk_hw *hw, unsigned long rate,
					  unsigned long parent_rate)
{
	struct clk_alpha_pll_postdiv *pll = to_clk_alpha_pll_postdiv(hw);
	int div;

	/* 16 -> 0xf, 8 -> 0x7, 4 -> 0x3, 2 -> 0x1, 1 -> 0x0 */
	div = DIV_ROUND_UP_ULL(parent_rate, rate) - 1;

	return regmap_update_bits(pll->clkr.regmap, PLL_USER_CTL(pll),
				  PLL_POST_DIV_MASK(pll) << PLL_POST_DIV_SHIFT,
				  div << PLL_POST_DIV_SHIFT);
}