#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_8__ {TYPE_1__* p_sw; } ;
struct TYPE_9__ {TYPE_2__ hca_or_sw; } ;
typedef  TYPE_3__ ftree_port_group_t ;
struct TYPE_7__ {scalar_t__ counter_up_changed; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ port_group_compare_load_up (TYPE_3__*,TYPE_3__*) ; 

__attribute__((used)) static inline void
bubble_sort_up(ftree_port_group_t ** p_group_array, uint32_t nmemb)
{
	uint32_t i = 0;
	uint32_t j = 0;
	ftree_port_group_t *tmp = p_group_array[0];

	/* As this function is a great number of times, we only go into the loop
	 * if one of the port counters has changed, thus saving some tests */
	if (tmp->hca_or_sw.p_sw->counter_up_changed == FALSE) {
		return;
	}
	/* While we did modifications on the array order */
	/* i may grew above array length but next loop will fail and tmp will be null for the next time
	 * this way we save a test i < nmemb for each pass through the loop */
	for (i = 0; tmp; i++) {
		/* Assume the array is orderd */
		tmp = NULL;
		/* Comparing elements j and j-1 */
		for (j = 1; j < (nmemb - i); j++) {
			/* If they are the wrong way around */
			if (port_group_compare_load_up(p_group_array[j],
						       p_group_array[j - 1]) < 0) {
				/* We invert them */
				tmp = p_group_array[j - 1];
				p_group_array[j - 1] = p_group_array[j];
				p_group_array[j] = tmp;
				/* This sets tmp != NULL so the main loop will make another pass */
			}
		}
	}

	/* We have reordered the array so as long noone changes the counter
	 * it's not necessary to do it again */
	p_group_array[0]->hca_or_sw.p_sw->counter_up_changed = FALSE;
}