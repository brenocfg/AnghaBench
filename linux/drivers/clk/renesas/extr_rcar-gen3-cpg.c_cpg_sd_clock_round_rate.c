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
struct sd_clock {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 long DIV_ROUND_CLOSEST (unsigned long,unsigned int) ; 
 unsigned int cpg_sd_clock_calc_div (struct sd_clock*,unsigned long,unsigned long) ; 
 struct sd_clock* to_sd_clock (struct clk_hw*) ; 

__attribute__((used)) static long cpg_sd_clock_round_rate(struct clk_hw *hw, unsigned long rate,
				      unsigned long *parent_rate)
{
	struct sd_clock *clock = to_sd_clock(hw);
	unsigned int div = cpg_sd_clock_calc_div(clock, rate, *parent_rate);

	return DIV_ROUND_CLOSEST(*parent_rate, div);
}