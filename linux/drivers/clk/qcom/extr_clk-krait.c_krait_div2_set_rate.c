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
struct krait_div2_clk {int shift; int /*<<< orphan*/  offset; scalar_t__ lpl; int /*<<< orphan*/  width; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int LPL_SHIFT ; 
 int /*<<< orphan*/  krait_clock_reg_lock ; 
 int krait_get_l2_indirect_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krait_set_l2_indirect_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct krait_div2_clk* to_krait_div2_clk (struct clk_hw*) ; 

__attribute__((used)) static int krait_div2_set_rate(struct clk_hw *hw, unsigned long rate,
			       unsigned long parent_rate)
{
	struct krait_div2_clk *d = to_krait_div2_clk(hw);
	unsigned long flags;
	u32 val;
	u32 mask = BIT(d->width) - 1;

	if (d->lpl)
		mask = mask << (d->shift + LPL_SHIFT) | mask << d->shift;

	spin_lock_irqsave(&krait_clock_reg_lock, flags);
	val = krait_get_l2_indirect_reg(d->offset);
	val &= ~mask;
	krait_set_l2_indirect_reg(d->offset, val);
	spin_unlock_irqrestore(&krait_clock_reg_lock, flags);

	return 0;
}