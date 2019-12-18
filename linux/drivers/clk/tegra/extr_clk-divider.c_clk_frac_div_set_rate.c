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
struct tegra_clk_frac_div {int shift; int flags; scalar_t__ lock; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int PERIPH_CLK_UART_DIV_ENB ; 
 int TEGRA_DIVIDER_FIXED ; 
 int TEGRA_DIVIDER_UART ; 
 int div_mask (struct tegra_clk_frac_div*) ; 
 int get_div (struct tegra_clk_frac_div*,unsigned long,unsigned long) ; 
 int pll_out_override (struct tegra_clk_frac_div*) ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 struct tegra_clk_frac_div* to_clk_frac_div (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_frac_div_set_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long parent_rate)
{
	struct tegra_clk_frac_div *divider = to_clk_frac_div(hw);
	int div;
	unsigned long flags = 0;
	u32 val;

	div = get_div(divider, rate, parent_rate);
	if (div < 0)
		return div;

	if (divider->lock)
		spin_lock_irqsave(divider->lock, flags);

	val = readl_relaxed(divider->reg);
	val &= ~(div_mask(divider) << divider->shift);
	val |= div << divider->shift;

	if (divider->flags & TEGRA_DIVIDER_UART) {
		if (div)
			val |= PERIPH_CLK_UART_DIV_ENB;
		else
			val &= ~PERIPH_CLK_UART_DIV_ENB;
	}

	if (divider->flags & TEGRA_DIVIDER_FIXED)
		val |= pll_out_override(divider);

	writel_relaxed(val, divider->reg);

	if (divider->lock)
		spin_unlock_irqrestore(divider->lock, flags);

	return 0;
}