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
struct clk_gate2 {scalar_t__* share_count; int bit_idx; int /*<<< orphan*/  lock; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct clk_gate2* to_clk_gate2 (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clk_gate2_disable(struct clk_hw *hw)
{
	struct clk_gate2 *gate = to_clk_gate2(hw);
	u32 reg;
	unsigned long flags = 0;

	spin_lock_irqsave(gate->lock, flags);

	if (gate->share_count) {
		if (WARN_ON(*gate->share_count == 0))
			goto out;
		else if (--(*gate->share_count) > 0)
			goto out;
	}

	reg = readl(gate->reg);
	reg &= ~(3 << gate->bit_idx);
	writel(reg, gate->reg);

out:
	spin_unlock_irqrestore(gate->lock, flags);
}