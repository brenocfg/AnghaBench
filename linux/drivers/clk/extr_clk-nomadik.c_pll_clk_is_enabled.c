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
struct clk_pll {int id; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ SRC_PLLCR ; 
 int SRC_PLLCR_PLL1EN ; 
 int SRC_PLLCR_PLL1OVER ; 
 int SRC_PLLCR_PLL2EN ; 
 int readl (scalar_t__) ; 
 scalar_t__ src_base ; 
 struct clk_pll* to_pll (struct clk_hw*) ; 

__attribute__((used)) static int pll_clk_is_enabled(struct clk_hw *hw)
{
	struct clk_pll *pll = to_pll(hw);
	u32 val;

	val = readl(src_base + SRC_PLLCR);
	if (pll->id == 1) {
		if (val & SRC_PLLCR_PLL1OVER)
			return !!(val & SRC_PLLCR_PLL1EN);
	} else if (pll->id == 2) {
		return !!(val & SRC_PLLCR_PLL2EN);
	}
	return 1;
}