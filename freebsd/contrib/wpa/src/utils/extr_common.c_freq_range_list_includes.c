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
struct wpa_freq_range_list {unsigned int num; TYPE_1__* range; } ;
struct TYPE_2__ {unsigned int min; unsigned int max; } ;

/* Variables and functions */

int freq_range_list_includes(const struct wpa_freq_range_list *list,
			     unsigned int freq)
{
	unsigned int i;

	if (list == NULL)
		return 0;

	for (i = 0; i < list->num; i++) {
		if (freq >= list->range[i].min && freq <= list->range[i].max)
			return 1;
	}

	return 0;
}