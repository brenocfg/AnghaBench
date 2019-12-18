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
struct clk_hw {int dummy; } ;
struct clk_fractional_divider {unsigned long nwidth; int mwidth; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENMASK (int,int /*<<< orphan*/ ) ; 
 unsigned long fls_long (unsigned long) ; 
 int /*<<< orphan*/  rational_best_approximation (unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*,unsigned long*) ; 
 struct clk_fractional_divider* to_clk_fd (struct clk_hw*) ; 

__attribute__((used)) static void clk_fd_general_approximation(struct clk_hw *hw, unsigned long rate,
					 unsigned long *parent_rate,
					 unsigned long *m, unsigned long *n)
{
	struct clk_fractional_divider *fd = to_clk_fd(hw);
	unsigned long scale;

	/*
	 * Get rate closer to *parent_rate to guarantee there is no overflow
	 * for m and n. In the result it will be the nearest rate left shifted
	 * by (scale - fd->nwidth) bits.
	 */
	scale = fls_long(*parent_rate / rate - 1);
	if (scale > fd->nwidth)
		rate <<= scale - fd->nwidth;

	rational_best_approximation(rate, *parent_rate,
			GENMASK(fd->mwidth - 1, 0), GENMASK(fd->nwidth - 1, 0),
			m, n);
}