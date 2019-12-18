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
typedef  int u32 ;
typedef  unsigned long u16 ;
struct lpc18xx_pll {scalar_t__ reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ LPC18XX_CGU_PLL1_CTRL ; 
 scalar_t__ LPC18XX_CGU_PLL1_STAT ; 
 int LPC18XX_PLL1_CTRL_DIRECT ; 
 int LPC18XX_PLL1_CTRL_FBSEL ; 
 int readl (scalar_t__) ; 
 struct lpc18xx_pll* to_lpc_pll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long lpc18xx_pll1_recalc_rate(struct clk_hw *hw,
					      unsigned long parent_rate)
{
	struct lpc18xx_pll *pll = to_lpc_pll(hw);
	u16 msel, nsel, psel;
	bool direct, fbsel;
	u32 stat, ctrl;

	stat = readl(pll->reg + LPC18XX_CGU_PLL1_STAT);
	ctrl = readl(pll->reg + LPC18XX_CGU_PLL1_CTRL);

	direct = (ctrl & LPC18XX_PLL1_CTRL_DIRECT) ? true : false;
	fbsel = (ctrl & LPC18XX_PLL1_CTRL_FBSEL) ? true : false;

	msel = ((ctrl >> 16) & 0xff) + 1;
	nsel = ((ctrl >> 12) & 0x3) + 1;

	if (direct || fbsel)
		return msel * (parent_rate / nsel);

	psel = (ctrl >>  8) & 0x3;
	psel = 1 << psel;

	return (msel / (2 * psel)) * (parent_rate / nsel);
}