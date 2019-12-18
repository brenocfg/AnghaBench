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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int CLK_SET_RATE_PARENT ; 
 void* DIV_ROUND_UP_ULL (int,unsigned int) ; 
 unsigned long ULONG_MAX ; 
 scalar_t__ _is_best_half_div (unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int clk_hw_get_flags (struct clk_hw*) ; 
 int /*<<< orphan*/  clk_hw_get_parent (struct clk_hw*) ; 
 unsigned long clk_hw_round_rate (int /*<<< orphan*/ ,int) ; 
 void* div_mask (int /*<<< orphan*/ ) ; 
 unsigned long min (unsigned long,unsigned long) ; 

__attribute__((used)) static int clk_half_divider_bestdiv(struct clk_hw *hw, unsigned long rate,
				    unsigned long *best_parent_rate, u8 width,
				    unsigned long flags)
{
	unsigned int i, bestdiv = 0;
	unsigned long parent_rate, best = 0, now, maxdiv;
	unsigned long parent_rate_saved = *best_parent_rate;

	if (!rate)
		rate = 1;

	maxdiv = div_mask(width);

	if (!(clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT)) {
		parent_rate = *best_parent_rate;
		bestdiv = DIV_ROUND_UP_ULL(((u64)parent_rate * 2), rate);
		if (bestdiv < 3)
			bestdiv = 0;
		else
			bestdiv = (bestdiv - 3) / 2;
		bestdiv = bestdiv > maxdiv ? maxdiv : bestdiv;
		return bestdiv;
	}

	/*
	 * The maximum divider we can use without overflowing
	 * unsigned long in rate * i below
	 */
	maxdiv = min(ULONG_MAX / rate, maxdiv);

	for (i = 0; i <= maxdiv; i++) {
		if (((u64)rate * (i * 2 + 3)) == ((u64)parent_rate_saved * 2)) {
			/*
			 * It's the most ideal case if the requested rate can be
			 * divided from parent clock without needing to change
			 * parent rate, so return the divider immediately.
			 */
			*best_parent_rate = parent_rate_saved;
			return i;
		}
		parent_rate = clk_hw_round_rate(clk_hw_get_parent(hw),
						((u64)rate * (i * 2 + 3)) / 2);
		now = DIV_ROUND_UP_ULL(((u64)parent_rate * 2),
				       (i * 2 + 3));

		if (_is_best_half_div(rate, now, best, flags)) {
			bestdiv = i;
			best = now;
			*best_parent_rate = parent_rate;
		}
	}

	if (!bestdiv) {
		bestdiv = div_mask(width);
		*best_parent_rate = clk_hw_round_rate(clk_hw_get_parent(hw), 1);
	}

	return bestdiv;
}