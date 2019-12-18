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
struct clk_div_table {int dummy; } ;

/* Variables and functions */
 unsigned long CLK_DIVIDER_POWER_OF_TWO ; 
 void* DIV_ROUND_UP_ULL (int /*<<< orphan*/ ,int) ; 
 int __rounddown_pow_of_two (int) ; 
 int __roundup_pow_of_two (int) ; 
 int _round_down_table (struct clk_div_table const*,int) ; 
 int _round_up_table (struct clk_div_table const*,int) ; 

__attribute__((used)) static int _div_round_closest(const struct clk_div_table *table,
			      unsigned long parent_rate, unsigned long rate,
			      unsigned long flags)
{
	int up, down;
	unsigned long up_rate, down_rate;

	up = DIV_ROUND_UP_ULL((u64)parent_rate, rate);
	down = parent_rate / rate;

	if (flags & CLK_DIVIDER_POWER_OF_TWO) {
		up = __roundup_pow_of_two(up);
		down = __rounddown_pow_of_two(down);
	} else if (table) {
		up = _round_up_table(table, up);
		down = _round_down_table(table, down);
	}

	up_rate = DIV_ROUND_UP_ULL((u64)parent_rate, up);
	down_rate = DIV_ROUND_UP_ULL((u64)parent_rate, down);

	return (rate - up_rate) <= (down_rate - rate) ? up : down;
}