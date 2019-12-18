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
typedef  int /*<<< orphan*/  u32 ;
struct clk_sccg_pll {scalar_t__ base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ PLL_CFG0 ; 
 int /*<<< orphan*/  PLL_PD_MASK ; 
 int clk_sccg_pll_wait_lock (struct clk_sccg_pll*) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 struct clk_sccg_pll* to_clk_sccg_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int clk_sccg_pll_prepare(struct clk_hw *hw)
{
	struct clk_sccg_pll *pll = to_clk_sccg_pll(hw);
	u32 val;

	val = readl_relaxed(pll->base + PLL_CFG0);
	val &= ~PLL_PD_MASK;
	writel_relaxed(val, pll->base + PLL_CFG0);

	return clk_sccg_pll_wait_lock(pll);
}