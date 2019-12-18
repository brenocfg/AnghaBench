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
struct clk_div_table {int dummy; } ;

/* Variables and functions */
 unsigned long CLK_DIVIDER_POWER_OF_TWO ; 
 int __roundup_pow_of_two (int) ; 
 int _round_up_table (struct clk_div_table const*,int) ; 

__attribute__((used)) static int _next_div(const struct clk_div_table *table, int div,
		     unsigned long flags)
{
	div++;

	if (flags & CLK_DIVIDER_POWER_OF_TWO)
		return __roundup_pow_of_two(div);
	if (table)
		return _round_up_table(table, div);

	return div;
}