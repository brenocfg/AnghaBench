#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct clk_hw {int dummy; } ;
struct TYPE_4__ {struct regmap* regmap; } ;
struct clk_alpha_pll_postdiv {int num_post_div; TYPE_1__* post_div_table; TYPE_2__ clkr; } ;
struct TYPE_3__ {int div; int val; } ;

/* Variables and functions */
 int DIV_ROUND_UP_ULL (unsigned long,unsigned long) ; 
 int PLL_POST_DIV_MASK (struct clk_alpha_pll_postdiv*) ; 
 int PLL_POST_DIV_SHIFT ; 
 int /*<<< orphan*/  PLL_USER_CTL (struct clk_alpha_pll_postdiv*) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 
 struct clk_alpha_pll_postdiv* to_clk_alpha_pll_postdiv (struct clk_hw*) ; 

__attribute__((used)) static int
clk_trion_pll_postdiv_set_rate(struct clk_hw *hw, unsigned long rate,
			       unsigned long parent_rate)
{
	struct clk_alpha_pll_postdiv *pll = to_clk_alpha_pll_postdiv(hw);
	struct regmap *regmap = pll->clkr.regmap;
	int i, val = 0, div;

	div = DIV_ROUND_UP_ULL(parent_rate, rate);
	for (i = 0; i < pll->num_post_div; i++) {
		if (pll->post_div_table[i].div == div) {
			val = pll->post_div_table[i].val;
			break;
		}
	}

	return regmap_update_bits(regmap, PLL_USER_CTL(pll),
				  PLL_POST_DIV_MASK(pll) << PLL_POST_DIV_SHIFT,
				  val << PLL_POST_DIV_SHIFT);
}