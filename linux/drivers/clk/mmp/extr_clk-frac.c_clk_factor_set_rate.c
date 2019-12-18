#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mmp_clk_factor_masks {unsigned long factor; unsigned long num_mask; unsigned long num_shift; unsigned long den_mask; unsigned long den_shift; } ;
struct mmp_clk_factor {int ftbl_cnt; scalar_t__ lock; int /*<<< orphan*/  base; TYPE_1__* ftbl; struct mmp_clk_factor_masks* masks; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {unsigned long den; unsigned long num; } ;

/* Variables and functions */
 unsigned long readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 struct mmp_clk_factor* to_clk_factor (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_factor_set_rate(struct clk_hw *hw, unsigned long drate,
				unsigned long prate)
{
	struct mmp_clk_factor *factor = to_clk_factor(hw);
	struct mmp_clk_factor_masks *masks = factor->masks;
	int i;
	unsigned long val;
	unsigned long rate = 0;
	unsigned long flags = 0;

	for (i = 0; i < factor->ftbl_cnt; i++) {
		rate = (((prate / 10000) * factor->ftbl[i].den) /
			(factor->ftbl[i].num * factor->masks->factor)) * 10000;
		if (rate > drate)
			break;
	}
	if (i > 0)
		i--;

	if (factor->lock)
		spin_lock_irqsave(factor->lock, flags);

	val = readl_relaxed(factor->base);

	val &= ~(masks->num_mask << masks->num_shift);
	val |= (factor->ftbl[i].num & masks->num_mask) << masks->num_shift;

	val &= ~(masks->den_mask << masks->den_shift);
	val |= (factor->ftbl[i].den & masks->den_mask) << masks->den_shift;

	writel_relaxed(val, factor->base);

	if (factor->lock)
		spin_unlock_irqrestore(factor->lock, flags);

	return 0;
}