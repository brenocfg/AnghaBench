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
struct clk_hw {int dummy; } ;
struct clk_divider_gate {unsigned int cached_val; } ;
struct clk_divider {unsigned int shift; int /*<<< orphan*/  width; int /*<<< orphan*/  flags; int /*<<< orphan*/  table; int /*<<< orphan*/  lock; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 unsigned int clk_div_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_hw_is_enabled (struct clk_hw*) ; 
 unsigned long divider_recalc_rate (struct clk_hw*,unsigned long,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct clk_divider* to_clk_divider (struct clk_hw*) ; 
 struct clk_divider_gate* to_clk_divider_gate (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_divider_gate_recalc_rate(struct clk_hw *hw,
						  unsigned long parent_rate)
{
	struct clk_divider_gate *div_gate = to_clk_divider_gate(hw);
	struct clk_divider *div = to_clk_divider(hw);
	unsigned long flags = 0;
	unsigned int val;

	spin_lock_irqsave(div->lock, flags);

	if (!clk_hw_is_enabled(hw)) {
		val = div_gate->cached_val;
	} else {
		val = readl(div->reg) >> div->shift;
		val &= clk_div_mask(div->width);
	}

	spin_unlock_irqrestore(div->lock, flags);

	if (!val)
		return 0;

	return divider_recalc_rate(hw, parent_rate, val, div->table,
				   div->flags, div->width);
}