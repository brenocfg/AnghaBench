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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct clk_sccg_pll {int /*<<< orphan*/  bypass1; int /*<<< orphan*/  bypass2; scalar_t__ base; int /*<<< orphan*/  parent; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ PLL_CFG0 ; 
 int SSCG_PLL_BYPASS1_MASK ; 
 int SSCG_PLL_BYPASS2_MASK ; 
 int readl (scalar_t__) ; 
 struct clk_sccg_pll* to_clk_sccg_pll (struct clk_hw*) ; 

__attribute__((used)) static u8 clk_sccg_pll_get_parent(struct clk_hw *hw)
{
	struct clk_sccg_pll *pll = to_clk_sccg_pll(hw);
	u32 val;
	u8 ret = pll->parent;

	val = readl(pll->base + PLL_CFG0);
	if (val & SSCG_PLL_BYPASS2_MASK)
		ret = pll->bypass2;
	else if (val & SSCG_PLL_BYPASS1_MASK)
		ret = pll->bypass1;
	return ret;
}