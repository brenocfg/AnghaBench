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
typedef  int u64 ;
typedef  int u32 ;
struct samsung_clk_pll {int /*<<< orphan*/  con_reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int PLL2550XX_M_MASK ; 
 int PLL2550XX_M_SHIFT ; 
 int PLL2550XX_P_MASK ; 
 int PLL2550XX_P_SHIFT ; 
 int PLL2550XX_S_MASK ; 
 int PLL2550XX_S_SHIFT ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 struct samsung_clk_pll* to_clk_pll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long samsung_pll2550xx_recalc_rate(struct clk_hw *hw,
				unsigned long parent_rate)
{
	struct samsung_clk_pll *pll = to_clk_pll(hw);
	u32 mdiv, pdiv, sdiv, pll_con;
	u64 fvco = parent_rate;

	pll_con = readl_relaxed(pll->con_reg);
	mdiv = (pll_con >> PLL2550XX_M_SHIFT) & PLL2550XX_M_MASK;
	pdiv = (pll_con >> PLL2550XX_P_SHIFT) & PLL2550XX_P_MASK;
	sdiv = (pll_con >> PLL2550XX_S_SHIFT) & PLL2550XX_S_MASK;

	fvco *= mdiv;
	do_div(fvco, (pdiv << sdiv));

	return (unsigned long)fvco;
}