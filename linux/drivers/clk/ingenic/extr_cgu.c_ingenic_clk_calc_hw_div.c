#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int bits; unsigned int* div_table; } ;
struct ingenic_cgu_clk_info {TYPE_1__ div; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int
ingenic_clk_calc_hw_div(const struct ingenic_cgu_clk_info *clk_info,
			unsigned int div)
{
	unsigned int i;

	for (i = 0; i < (1 << clk_info->div.bits)
				&& clk_info->div.div_table[i]; i++) {
		if (clk_info->div.div_table[i] >= div)
			return i;
	}

	return i - 1;
}