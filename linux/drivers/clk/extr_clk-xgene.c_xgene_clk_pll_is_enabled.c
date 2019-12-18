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
struct xgene_clk_pll {scalar_t__ pll_offset; scalar_t__ reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int REGSPEC_RESET_F1_MASK ; 
 int /*<<< orphan*/  clk_hw_get_name (struct clk_hw*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,char*) ; 
 struct xgene_clk_pll* to_xgene_clk_pll (struct clk_hw*) ; 
 int xgene_clk_read (scalar_t__) ; 

__attribute__((used)) static int xgene_clk_pll_is_enabled(struct clk_hw *hw)
{
	struct xgene_clk_pll *pllclk = to_xgene_clk_pll(hw);
	u32 data;

	data = xgene_clk_read(pllclk->reg + pllclk->pll_offset);
	pr_debug("%s pll %s\n", clk_hw_get_name(hw),
		data & REGSPEC_RESET_F1_MASK ? "disabled" : "enabled");

	return data & REGSPEC_RESET_F1_MASK ? 0 : 1;
}