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
struct TYPE_2__ {int width_div; } ;
struct mmp_clk_mix {int div_flags; struct clk_div_table* div_table; TYPE_1__ reg_info; } ;
struct clk_div_table {int div; } ;

/* Variables and functions */
 int CLK_DIVIDER_ONE_BASED ; 
 int CLK_DIVIDER_POWER_OF_TWO ; 

__attribute__((used)) static unsigned int _get_maxdiv(struct mmp_clk_mix *mix)
{
	unsigned int div_mask = (1 << mix->reg_info.width_div) - 1;
	unsigned int maxdiv = 0;
	struct clk_div_table *clkt;

	if (mix->div_flags & CLK_DIVIDER_ONE_BASED)
		return div_mask;
	if (mix->div_flags & CLK_DIVIDER_POWER_OF_TWO)
		return 1 << div_mask;
	if (mix->div_table) {
		for (clkt = mix->div_table; clkt->div; clkt++)
			if (clkt->div > maxdiv)
				maxdiv = clkt->div;
		return maxdiv;
	}
	return div_mask + 1;
}