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
struct frac_rate_tbl {unsigned long div; } ;
struct clk_hw {int dummy; } ;
struct clk_frac {scalar_t__ lock; int /*<<< orphan*/  reg; int /*<<< orphan*/  rtbl_cnt; struct frac_rate_tbl* rtbl; } ;

/* Variables and functions */
 unsigned long DIV_FACTOR_MASK ; 
 int /*<<< orphan*/  clk_round_rate_index (struct clk_hw*,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  frac_calc_rate ; 
 unsigned long readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 struct clk_frac* to_clk_frac (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_frac_set_rate(struct clk_hw *hw, unsigned long drate,
				unsigned long prate)
{
	struct clk_frac *frac = to_clk_frac(hw);
	struct frac_rate_tbl *rtbl = frac->rtbl;
	unsigned long flags = 0, val;
	int i;

	clk_round_rate_index(hw, drate, prate, frac_calc_rate, frac->rtbl_cnt,
			&i);

	if (frac->lock)
		spin_lock_irqsave(frac->lock, flags);

	val = readl_relaxed(frac->reg) & ~DIV_FACTOR_MASK;
	val |= rtbl[i].div & DIV_FACTOR_MASK;
	writel_relaxed(val, frac->reg);

	if (frac->lock)
		spin_unlock_irqrestore(frac->lock, flags);

	return 0;
}