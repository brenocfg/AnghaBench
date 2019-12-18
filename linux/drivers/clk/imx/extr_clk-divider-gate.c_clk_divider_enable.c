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
struct clk_divider {int shift; int /*<<< orphan*/  lock; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  clk_hw_get_name (struct clk_hw*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct clk_divider* to_clk_divider (struct clk_hw*) ; 
 struct clk_divider_gate* to_clk_divider_gate (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_divider_enable(struct clk_hw *hw)
{
	struct clk_divider_gate *div_gate = to_clk_divider_gate(hw);
	struct clk_divider *div = to_clk_divider(hw);
	unsigned long flags = 0;
	u32 val;

	if (!div_gate->cached_val) {
		pr_err("%s: no valid preset rate\n", clk_hw_get_name(hw));
		return -EINVAL;
	}

	spin_lock_irqsave(div->lock, flags);
	/* restore div val */
	val = readl(div->reg);
	val |= div_gate->cached_val << div->shift;
	writel(val, div->reg);

	spin_unlock_irqrestore(div->lock, flags);

	return 0;
}