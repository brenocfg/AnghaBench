#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_5__ {size_t down_port_groups_num; size_t min_counter_down; TYPE_1__** down_port_groups; } ;
typedef  TYPE_2__ ftree_sw_t ;
struct TYPE_4__ {size_t counter_down; } ;

/* Variables and functions */

__attribute__((used)) static inline void recalculate_min_counter_down(ftree_sw_t * p_sw)
{
	uint32_t min = (1 << 30);
	uint32_t i;
	for (i = 0; i < p_sw->down_port_groups_num; i++) {
		if (p_sw->down_port_groups[i]->counter_down < min) {
			min = p_sw->down_port_groups[i]->counter_down;
		}
	}
	p_sw->min_counter_down = min;
	return;
}