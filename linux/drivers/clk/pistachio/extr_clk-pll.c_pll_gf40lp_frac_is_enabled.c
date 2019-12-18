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
struct pistachio_clk_pll {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_CTRL3 ; 
 int PLL_FRAC_CTRL3_PD ; 
 int pll_readl (struct pistachio_clk_pll*,int /*<<< orphan*/ ) ; 
 struct pistachio_clk_pll* to_pistachio_pll (struct clk_hw*) ; 

__attribute__((used)) static int pll_gf40lp_frac_is_enabled(struct clk_hw *hw)
{
	struct pistachio_clk_pll *pll = to_pistachio_pll(hw);

	return !(pll_readl(pll, PLL_CTRL3) & PLL_FRAC_CTRL3_PD);
}