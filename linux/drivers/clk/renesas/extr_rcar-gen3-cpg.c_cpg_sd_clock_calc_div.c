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
struct sd_clock {unsigned int div_num; TYPE_1__* div_table; } ;
struct TYPE_2__ {unsigned int div; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_CLOSEST (unsigned long,unsigned int) ; 
 unsigned long ULONG_MAX ; 

__attribute__((used)) static unsigned int cpg_sd_clock_calc_div(struct sd_clock *clock,
					  unsigned long rate,
					  unsigned long parent_rate)
{
	unsigned long calc_rate, diff, diff_min = ULONG_MAX;
	unsigned int i, best_div = 0;

	for (i = 0; i < clock->div_num; i++) {
		calc_rate = DIV_ROUND_CLOSEST(parent_rate,
					      clock->div_table[i].div);
		diff = calc_rate > rate ? calc_rate - rate : rate - calc_rate;
		if (diff < diff_min) {
			best_div = clock->div_table[i].div;
			diff_min = diff;
		}
	}

	return best_div;
}