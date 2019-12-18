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
typedef  int u64 ;
typedef  int u32 ;
struct clk_hw {int dummy; } ;
struct clk_frac {int width; int shift; int /*<<< orphan*/  busy; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  do_div (int,unsigned long) ; 
 int mxs_clk_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxs_lock ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct clk_frac* to_clk_frac (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_frac_set_rate(struct clk_hw *hw, unsigned long rate,
			     unsigned long parent_rate)
{
	struct clk_frac *frac = to_clk_frac(hw);
	unsigned long flags;
	u32 div, val;
	u64 tmp;

	if (rate > parent_rate)
		return -EINVAL;

	tmp = rate;
	tmp <<= frac->width;
	do_div(tmp, parent_rate);
	div = tmp;

	if (!div)
		return -EINVAL;

	spin_lock_irqsave(&mxs_lock, flags);

	val = readl_relaxed(frac->reg);
	val &= ~(((1 << frac->width) - 1) << frac->shift);
	val |= div << frac->shift;
	writel_relaxed(val, frac->reg);

	spin_unlock_irqrestore(&mxs_lock, flags);

	return mxs_clk_wait(frac->reg, frac->busy);
}