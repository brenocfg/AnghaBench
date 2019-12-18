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
struct hsdk_pll_clk {int /*<<< orphan*/  dev; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGU_PLL_CTRL ; 
 int CGU_PLL_CTRL_BYPASS ; 
 int CGU_PLL_CTRL_FBDIV_MASK ; 
 int CGU_PLL_CTRL_FBDIV_SHIFT ; 
 int CGU_PLL_CTRL_IDIV_MASK ; 
 int CGU_PLL_CTRL_IDIV_SHIFT ; 
 int CGU_PLL_CTRL_ODIV_MASK ; 
 int CGU_PLL_CTRL_ODIV_SHIFT ; 
 int CGU_PLL_CTRL_PD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int hsdk_pll_read (struct hsdk_pll_clk*,int /*<<< orphan*/ ) ; 
 struct hsdk_pll_clk* to_hsdk_pll_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long hsdk_pll_recalc_rate(struct clk_hw *hw,
					  unsigned long parent_rate)
{
	u32 val;
	u64 rate;
	u32 idiv, fbdiv, odiv;
	struct hsdk_pll_clk *clk = to_hsdk_pll_clk(hw);

	val = hsdk_pll_read(clk, CGU_PLL_CTRL);

	dev_dbg(clk->dev, "current configuration: %#x\n", val);

	/* Check if PLL is disabled */
	if (val & CGU_PLL_CTRL_PD)
		return 0;

	/* Check if PLL is bypassed */
	if (val & CGU_PLL_CTRL_BYPASS)
		return parent_rate;

	/* input divider = reg.idiv + 1 */
	idiv = 1 + ((val & CGU_PLL_CTRL_IDIV_MASK) >> CGU_PLL_CTRL_IDIV_SHIFT);
	/* fb divider = 2*(reg.fbdiv + 1) */
	fbdiv = 2 * (1 + ((val & CGU_PLL_CTRL_FBDIV_MASK) >> CGU_PLL_CTRL_FBDIV_SHIFT));
	/* output divider = 2^(reg.odiv) */
	odiv = 1 << ((val & CGU_PLL_CTRL_ODIV_MASK) >> CGU_PLL_CTRL_ODIV_SHIFT);

	rate = (u64)parent_rate * fbdiv;
	do_div(rate, idiv * odiv);

	return rate;
}