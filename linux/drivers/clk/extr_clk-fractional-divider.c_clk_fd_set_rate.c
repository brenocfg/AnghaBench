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
typedef  unsigned long u32 ;
struct clk_hw {int dummy; } ;
struct clk_fractional_divider {int flags; unsigned long mmask; unsigned long nmask; unsigned long mshift; unsigned long nshift; scalar_t__ lock; scalar_t__ nwidth; scalar_t__ mwidth; } ;

/* Variables and functions */
 int CLK_FRAC_DIVIDER_ZERO_BASED ; 
 int /*<<< orphan*/  GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __acquire (scalar_t__) ; 
 int /*<<< orphan*/  __release (scalar_t__) ; 
 unsigned long clk_fd_readl (struct clk_fractional_divider*) ; 
 int /*<<< orphan*/  clk_fd_writel (struct clk_fractional_divider*,unsigned long) ; 
 int /*<<< orphan*/  rational_best_approximation (unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 struct clk_fractional_divider* to_clk_fd (struct clk_hw*) ; 

__attribute__((used)) static int clk_fd_set_rate(struct clk_hw *hw, unsigned long rate,
			   unsigned long parent_rate)
{
	struct clk_fractional_divider *fd = to_clk_fd(hw);
	unsigned long flags = 0;
	unsigned long m, n;
	u32 val;

	rational_best_approximation(rate, parent_rate,
			GENMASK(fd->mwidth - 1, 0), GENMASK(fd->nwidth - 1, 0),
			&m, &n);

	if (fd->flags & CLK_FRAC_DIVIDER_ZERO_BASED) {
		m--;
		n--;
	}

	if (fd->lock)
		spin_lock_irqsave(fd->lock, flags);
	else
		__acquire(fd->lock);

	val = clk_fd_readl(fd);
	val &= ~(fd->mmask | fd->nmask);
	val |= (m << fd->mshift) | (n << fd->nshift);
	clk_fd_writel(fd, val);

	if (fd->lock)
		spin_unlock_irqrestore(fd->lock, flags);
	else
		__release(fd->lock);

	return 0;
}