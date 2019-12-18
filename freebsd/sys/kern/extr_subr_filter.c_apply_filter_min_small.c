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
typedef  scalar_t__ uint32_t ;
struct time_filter_small {TYPE_1__* entries; } ;
struct TYPE_2__ {scalar_t__ value; scalar_t__ time_up; } ;

/* Variables and functions */
 int NUM_FILTER_ENTRIES ; 
 int /*<<< orphan*/  check_update_times_small (struct time_filter_small*,scalar_t__,scalar_t__) ; 

uint32_t
apply_filter_min_small(struct time_filter_small *tf,
		       uint32_t value, uint32_t now)
{
	int i, j;
	
	if (value <= tf->entries[0].value) {
		/* Zap them all */
		for(i=0; i<NUM_FILTER_ENTRIES; i++) {
			tf->entries[i].value = value;
			tf->entries[i].time_up = now;
		}
		return (tf->entries[0].value);
	}
	for (j=1; j<NUM_FILTER_ENTRIES; j++) {
		if (value <= tf->entries[j].value) {
			for(i=j; i<NUM_FILTER_ENTRIES; i++) {
				tf->entries[i].value = value;
				tf->entries[i].time_up = now;
			}
			break;
		}
	}
	check_update_times_small(tf, value, now);
	return (tf->entries[0].value);
}