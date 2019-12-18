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
typedef  int /*<<< orphan*/  u64 ;
struct meson_sclk_div_data {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int CLK_SET_RATE_PARENT ; 
 unsigned long DIV_ROUND_UP_ULL (int /*<<< orphan*/ ,int) ; 
 unsigned long ULONG_MAX ; 
 scalar_t__ abs (unsigned long) ; 
 int clk_hw_get_flags (struct clk_hw*) ; 
 struct clk_hw* clk_hw_get_parent (struct clk_hw*) ; 
 unsigned long clk_hw_round_rate (struct clk_hw*,unsigned long) ; 
 unsigned long min (unsigned long,unsigned long) ; 
 int sclk_div_getdiv (struct clk_hw*,unsigned long,unsigned long,unsigned long) ; 
 void* sclk_div_maxdiv (struct meson_sclk_div_data*) ; 

__attribute__((used)) static int sclk_div_bestdiv(struct clk_hw *hw, unsigned long rate,
			    unsigned long *prate,
			    struct meson_sclk_div_data *sclk)
{
	struct clk_hw *parent = clk_hw_get_parent(hw);
	int bestdiv = 0, i;
	unsigned long maxdiv, now, parent_now;
	unsigned long best = 0, best_parent = 0;

	if (!rate)
		rate = 1;

	maxdiv = sclk_div_maxdiv(sclk);

	if (!(clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT))
		return sclk_div_getdiv(hw, rate, *prate, maxdiv);

	/*
	 * The maximum divider we can use without overflowing
	 * unsigned long in rate * i below
	 */
	maxdiv = min(ULONG_MAX / rate, maxdiv);

	for (i = 2; i <= maxdiv; i++) {
		/*
		 * It's the most ideal case if the requested rate can be
		 * divided from parent clock without needing to change
		 * parent rate, so return the divider immediately.
		 */
		if (rate * i == *prate)
			return i;

		parent_now = clk_hw_round_rate(parent, rate * i);
		now = DIV_ROUND_UP_ULL((u64)parent_now, i);

		if (abs(rate - now) < abs(rate - best)) {
			bestdiv = i;
			best = now;
			best_parent = parent_now;
		}
	}

	if (!bestdiv)
		bestdiv = sclk_div_maxdiv(sclk);
	else
		*prate = best_parent;

	return bestdiv;
}