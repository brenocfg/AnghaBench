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
struct dove_clk {int* divider_table; int div_bit_size; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (unsigned long,unsigned long) ; 
 int EINVAL ; 

__attribute__((used)) static int dove_calc_divider(const struct dove_clk *dc, unsigned long rate,
			     unsigned long parent_rate, bool set)
{
	unsigned int divider, max;

	divider = DIV_ROUND_CLOSEST(parent_rate, rate);

	if (dc->divider_table) {
		unsigned int i;

		for (i = 0; dc->divider_table[i]; i++)
			if (divider == dc->divider_table[i]) {
				divider = i;
				break;
			}

		if (!dc->divider_table[i])
			return -EINVAL;
	} else {
		max = 1 << dc->div_bit_size;

		if (set && (divider == 0 || divider >= max))
			return -EINVAL;
		if (divider >= max)
			divider = max - 1;
		else if (divider == 0)
			divider = 1;
	}

	return divider;
}