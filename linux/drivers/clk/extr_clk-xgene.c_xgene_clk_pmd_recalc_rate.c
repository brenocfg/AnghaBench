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
typedef  unsigned long u64 ;
typedef  unsigned long u32 ;
struct xgene_clk_pmd {unsigned long mask; unsigned long shift; int flags; unsigned long denom; scalar_t__ lock; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int XGENE_CLK_PMD_SCALE_INVERTED ; 
 int /*<<< orphan*/  __acquire (scalar_t__) ; 
 int /*<<< orphan*/  __release (scalar_t__) ; 
 int /*<<< orphan*/  do_div (unsigned long,unsigned long) ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 struct xgene_clk_pmd* to_xgene_clk_pmd (struct clk_hw*) ; 

__attribute__((used)) static unsigned long xgene_clk_pmd_recalc_rate(struct clk_hw *hw,
					       unsigned long parent_rate)
{
	struct xgene_clk_pmd *fd = to_xgene_clk_pmd(hw);
	unsigned long flags = 0;
	u64 ret, scale;
	u32 val;

	if (fd->lock)
		spin_lock_irqsave(fd->lock, flags);
	else
		__acquire(fd->lock);

	val = readl(fd->reg);

	if (fd->lock)
		spin_unlock_irqrestore(fd->lock, flags);
	else
		__release(fd->lock);

	ret = (u64)parent_rate;

	scale = (val & fd->mask) >> fd->shift;
	if (fd->flags & XGENE_CLK_PMD_SCALE_INVERTED)
		scale = fd->denom - scale;
	else
		scale++;

	/* freq = parent_rate * scaler / denom */
	do_div(ret, fd->denom);
	ret *= scale;
	if (ret == 0)
		ret = (u64)parent_rate;

	return ret;
}