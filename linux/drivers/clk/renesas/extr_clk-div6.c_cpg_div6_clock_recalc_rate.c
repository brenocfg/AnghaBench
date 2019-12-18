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
struct div6_clock {unsigned long div; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct div6_clock* to_div6_clock (struct clk_hw*) ; 

__attribute__((used)) static unsigned long cpg_div6_clock_recalc_rate(struct clk_hw *hw,
						unsigned long parent_rate)
{
	struct div6_clock *clock = to_div6_clock(hw);

	return parent_rate / clock->div;
}