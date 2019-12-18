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
struct clk_hw {int dummy; } ;
struct clk_divider_gate {int cached_val; } ;
struct clk_divider {int shift; int /*<<< orphan*/  lock; int /*<<< orphan*/  reg; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int clk_div_mask (int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct clk_divider* to_clk_divider (struct clk_hw*) ; 
 struct clk_divider_gate* to_clk_divider_gate (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clk_divider_disable(struct clk_hw *hw)
{
	struct clk_divider_gate *div_gate = to_clk_divider_gate(hw);
	struct clk_divider *div = to_clk_divider(hw);
	unsigned long flags = 0;
	u32 val;

	spin_lock_irqsave(div->lock, flags);

	/* store the current div val */
	val = readl(div->reg) >> div->shift;
	val &= clk_div_mask(div->width);
	div_gate->cached_val = val;
	writel(0, div->reg);

	spin_unlock_irqrestore(div->lock, flags);
}