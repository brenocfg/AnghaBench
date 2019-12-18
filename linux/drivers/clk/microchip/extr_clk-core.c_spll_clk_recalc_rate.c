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
struct pic32_sys_pll {unsigned long idiv; int /*<<< orphan*/  ctrl_reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int PLL_MULT_MASK ; 
 int PLL_MULT_SHIFT ; 
 int PLL_ODIV_MASK ; 
 int PLL_ODIV_SHIFT ; 
 struct pic32_sys_pll* clkhw_to_spll (struct clk_hw*) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int spll_odiv_to_divider (int) ; 

__attribute__((used)) static unsigned long spll_clk_recalc_rate(struct clk_hw *hw,
					  unsigned long parent_rate)
{
	struct pic32_sys_pll *pll = clkhw_to_spll(hw);
	unsigned long pll_in_rate;
	u32 mult, odiv, div, v;
	u64 rate64;

	v = readl(pll->ctrl_reg);
	odiv = ((v >> PLL_ODIV_SHIFT) & PLL_ODIV_MASK);
	mult = ((v >> PLL_MULT_SHIFT) & PLL_MULT_MASK) + 1;
	div = spll_odiv_to_divider(odiv);

	/* pll_in_rate = parent_rate / idiv
	 * pll_out_rate = pll_in_rate * mult / div;
	 */
	pll_in_rate = parent_rate / pll->idiv;
	rate64 = pll_in_rate;
	rate64 *= mult;
	do_div(rate64, div);

	return rate64;
}