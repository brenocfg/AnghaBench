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
struct clk_pll14xx {scalar_t__ base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int KDIV_MASK ; 
 int MDIV_MASK ; 
 int MDIV_SHIFT ; 
 int PDIV_MASK ; 
 int PDIV_SHIFT ; 
 int SDIV_MASK ; 
 int SDIV_SHIFT ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int readl_relaxed (scalar_t__) ; 
 struct clk_pll14xx* to_clk_pll14xx (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_pll1443x_recalc_rate(struct clk_hw *hw,
						  unsigned long parent_rate)
{
	struct clk_pll14xx *pll = to_clk_pll14xx(hw);
	u32 mdiv, pdiv, sdiv, pll_div_ctl0, pll_div_ctl1;
	short int kdiv;
	u64 fvco = parent_rate;

	pll_div_ctl0 = readl_relaxed(pll->base + 4);
	pll_div_ctl1 = readl_relaxed(pll->base + 8);
	mdiv = (pll_div_ctl0 & MDIV_MASK) >> MDIV_SHIFT;
	pdiv = (pll_div_ctl0 & PDIV_MASK) >> PDIV_SHIFT;
	sdiv = (pll_div_ctl0 & SDIV_MASK) >> SDIV_SHIFT;
	kdiv = pll_div_ctl1 & KDIV_MASK;

	/* fvco = (m * 65536 + k) * Fin / (p * 65536) */
	fvco *= (mdiv * 65536 + kdiv);
	pdiv *= 65536;

	do_div(fvco, pdiv << sdiv);

	return fvco;
}