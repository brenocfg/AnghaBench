#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  bypass; } ;
struct clk_sccg_pll {scalar_t__ base; TYPE_1__ setup; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PLL_CFG0 ; 
 int /*<<< orphan*/  SSCG_PLL_BYPASS_MASK ; 
 int clk_sccg_pll_wait_lock (struct clk_sccg_pll*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct clk_sccg_pll* to_clk_sccg_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int clk_sccg_pll_set_parent(struct clk_hw *hw, u8 index)
{
	struct clk_sccg_pll *pll = to_clk_sccg_pll(hw);
	u32 val;

	val = readl(pll->base + PLL_CFG0);
	val &= ~SSCG_PLL_BYPASS_MASK;
	val |= FIELD_PREP(SSCG_PLL_BYPASS_MASK, pll->setup.bypass);
	writel(val, pll->base + PLL_CFG0);

	return clk_sccg_pll_wait_lock(pll);
}