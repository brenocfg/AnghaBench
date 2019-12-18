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
struct zynq_pll {int /*<<< orphan*/  lock; int /*<<< orphan*/  pll_ctrl; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int PLLCTRL_PWRDWN_MASK ; 
 int PLLCTRL_RESET_MASK ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct zynq_pll* to_zynq_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynq_pll_is_enabled (struct clk_hw*) ; 

__attribute__((used)) static void zynq_pll_disable(struct clk_hw *hw)
{
	unsigned long flags = 0;
	u32 reg;
	struct zynq_pll *clk = to_zynq_pll(hw);

	if (!zynq_pll_is_enabled(hw))
		return;

	pr_info("PLL: shutdown\n");

	/* shut down PLL */
	spin_lock_irqsave(clk->lock, flags);

	reg = readl(clk->pll_ctrl);
	reg |= PLLCTRL_RESET_MASK | PLLCTRL_PWRDWN_MASK;
	writel(reg, clk->pll_ctrl);

	spin_unlock_irqrestore(clk->lock, flags);
}