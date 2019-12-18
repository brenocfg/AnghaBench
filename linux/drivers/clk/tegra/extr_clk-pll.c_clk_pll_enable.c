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
struct tegra_clk_pll {scalar_t__ lock; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _clk_pll_enable (struct clk_hw*) ; 
 scalar_t__ clk_pll_is_enabled (struct clk_hw*) ; 
 int clk_pll_wait_for_lock (struct tegra_clk_pll*) ; 
 int /*<<< orphan*/  pll_clk_start_ss (struct tegra_clk_pll*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 struct tegra_clk_pll* to_clk_pll (struct clk_hw*) ; 

__attribute__((used)) static int clk_pll_enable(struct clk_hw *hw)
{
	struct tegra_clk_pll *pll = to_clk_pll(hw);
	unsigned long flags = 0;
	int ret;

	if (clk_pll_is_enabled(hw))
		return 0;

	if (pll->lock)
		spin_lock_irqsave(pll->lock, flags);

	_clk_pll_enable(hw);

	ret = clk_pll_wait_for_lock(pll);

	pll_clk_start_ss(pll);

	if (pll->lock)
		spin_unlock_irqrestore(pll->lock, flags);

	return ret;
}