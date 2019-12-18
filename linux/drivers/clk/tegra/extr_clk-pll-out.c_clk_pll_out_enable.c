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
struct tegra_clk_pll_out {scalar_t__ lock; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int pll_out_enb (struct tegra_clk_pll_out*) ; 
 int pll_out_rst (struct tegra_clk_pll_out*) ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 struct tegra_clk_pll_out* to_clk_pll_out (struct clk_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_pll_out_enable(struct clk_hw *hw)
{
	struct tegra_clk_pll_out *pll_out = to_clk_pll_out(hw);
	unsigned long flags = 0;
	u32 val;

	if (pll_out->lock)
		spin_lock_irqsave(pll_out->lock, flags);

	val = readl_relaxed(pll_out->reg);

	val |= (pll_out_enb(pll_out) | pll_out_rst(pll_out));

	writel_relaxed(val, pll_out->reg);
	udelay(2);

	if (pll_out->lock)
		spin_unlock_irqrestore(pll_out->lock, flags);

	return 0;
}