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
struct clk_hw {int dummy; } ;
struct clk_fractional_divider {unsigned long mmask; unsigned long mshift; unsigned long nmask; unsigned long nshift; int flags; scalar_t__ lock; } ;

/* Variables and functions */
 int CLK_FRAC_DIVIDER_ZERO_BASED ; 
 int /*<<< orphan*/  __acquire (scalar_t__) ; 
 int /*<<< orphan*/  __release (scalar_t__) ; 
 unsigned long clk_fd_readl (struct clk_fractional_divider*) ; 
 int /*<<< orphan*/  do_div (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 struct clk_fractional_divider* to_clk_fd (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_fd_recalc_rate(struct clk_hw *hw,
					unsigned long parent_rate)
{
	struct clk_fractional_divider *fd = to_clk_fd(hw);
	unsigned long flags = 0;
	unsigned long m, n;
	u32 val;
	u64 ret;

	if (fd->lock)
		spin_lock_irqsave(fd->lock, flags);
	else
		__acquire(fd->lock);

	val = clk_fd_readl(fd);

	if (fd->lock)
		spin_unlock_irqrestore(fd->lock, flags);
	else
		__release(fd->lock);

	m = (val & fd->mmask) >> fd->mshift;
	n = (val & fd->nmask) >> fd->nshift;

	if (fd->flags & CLK_FRAC_DIVIDER_ZERO_BASED) {
		m++;
		n++;
	}

	if (!n || !m)
		return parent_rate;

	ret = (u64)parent_rate * m;
	do_div(ret, n);

	return ret;
}