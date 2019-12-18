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
typedef  scalar_t__ uint64_t ;
typedef  void* uint32_t ;
struct time_filter {TYPE_1__* entries; } ;
struct TYPE_2__ {scalar_t__ value; void* time_up; } ;

/* Variables and functions */
 int NUM_FILTER_ENTRIES ; 
 int /*<<< orphan*/  check_update_times (struct time_filter*,scalar_t__,void*) ; 

uint32_t
apply_filter_max(struct time_filter *tf, uint64_t value, uint32_t now)
{
	int i, j;
	
	if (value >= tf->entries[0].value) {
		/* Zap them all */
		for(i=0; i<NUM_FILTER_ENTRIES; i++) {
			tf->entries[i].value = value;
			tf->entries[i].time_up = now;
		}
		return (tf->entries[0].value);
	}
	for (j=1; j<NUM_FILTER_ENTRIES; j++) {
		if (value >= tf->entries[j].value) {
			for(i=j; i<NUM_FILTER_ENTRIES; i++) {
				tf->entries[i].value = value;
				tf->entries[i].time_up = now;
			}
			break;
		}
	}
	check_update_times(tf, value, now);
	return (tf->entries[0].value);
}