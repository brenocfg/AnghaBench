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
struct clk_div_table {int dummy; } ;

/* Variables and functions */
 unsigned long CLK_DIVIDER_MAX_AT_ZERO ; 
 unsigned long CLK_DIVIDER_ONE_BASED ; 
 unsigned long CLK_DIVIDER_POWER_OF_TWO ; 
 unsigned int __ffs (unsigned int) ; 
 unsigned int _get_table_val (struct clk_div_table const*,unsigned int) ; 
 int clk_div_mask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int _get_val(const struct clk_div_table *table,
			     unsigned int div, unsigned long flags, u8 width)
{
	if (flags & CLK_DIVIDER_ONE_BASED)
		return div;
	if (flags & CLK_DIVIDER_POWER_OF_TWO)
		return __ffs(div);
	if (flags & CLK_DIVIDER_MAX_AT_ZERO)
		return (div == clk_div_mask(width) + 1) ? 0 : div;
	if (table)
		return  _get_table_val(table, div);
	return div - 1;
}