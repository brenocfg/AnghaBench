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
typedef  unsigned int u32 ;
struct clk_hw {int dummy; } ;
struct clk_fixup_div {int /*<<< orphan*/  (* fixup ) (unsigned int*) ;} ;
struct clk_divider {unsigned int shift; int /*<<< orphan*/  lock; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 unsigned int div_mask (struct clk_divider*) ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (unsigned int*) ; 
 struct clk_divider* to_clk_divider (struct clk_hw*) ; 
 struct clk_fixup_div* to_clk_fixup_div (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_fixup_div_set_rate(struct clk_hw *hw, unsigned long rate,
			    unsigned long parent_rate)
{
	struct clk_fixup_div *fixup_div = to_clk_fixup_div(hw);
	struct clk_divider *div = to_clk_divider(hw);
	unsigned int divider, value;
	unsigned long flags = 0;
	u32 val;

	divider = parent_rate / rate;

	/* Zero based divider */
	value = divider - 1;

	if (value > div_mask(div))
		value = div_mask(div);

	spin_lock_irqsave(div->lock, flags);

	val = readl(div->reg);
	val &= ~(div_mask(div) << div->shift);
	val |= value << div->shift;
	fixup_div->fixup(&val);
	writel(val, div->reg);

	spin_unlock_irqrestore(div->lock, flags);

	return 0;
}