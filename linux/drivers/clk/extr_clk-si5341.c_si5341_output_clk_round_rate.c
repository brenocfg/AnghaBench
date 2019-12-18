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

/* Variables and functions */
 int CLK_SET_RATE_PARENT ; 
 int clk_hw_get_flags (struct clk_hw*) ; 

__attribute__((used)) static long si5341_output_clk_round_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long *parent_rate)
{
	unsigned long r;

	r = *parent_rate >> 1;

	/* If rate is an even divisor, no changes to parent required */
	if (r && !(r % rate))
		return (long)rate;

	if (clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT) {
		if (rate > 200000000) {
			/* minimum r-divider is 2 */
			r = 2;
		} else {
			/* Take a parent frequency near 400 MHz */
			r = (400000000u / rate) & ~1;
		}
		*parent_rate = r * rate;
	} else {
		/* We cannot change our parent's rate, report what we can do */
		r /= rate;
		rate = *parent_rate / (r << 1);
	}

	return rate;
}