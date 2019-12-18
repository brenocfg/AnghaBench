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
 int _is_valid_table_div (struct clk_div_table const*,unsigned int) ; 
 int is_power_of_2 (unsigned int) ; 

__attribute__((used)) static bool _is_valid_div(const struct clk_div_table *table, unsigned int div,
			  unsigned long flags)
{
	if (flags & CLK_DIVIDER_POWER_OF_TWO)
		return is_power_of_2(div);
	if (table)
		return _is_valid_table_div(table, div);
	return true;
}