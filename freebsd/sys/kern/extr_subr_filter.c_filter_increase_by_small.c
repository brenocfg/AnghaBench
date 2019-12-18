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
typedef  void* uint32_t ;
struct time_filter_small {TYPE_1__* entries; } ;
struct TYPE_2__ {void* time_up; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int NUM_FILTER_ENTRIES ; 

void
filter_increase_by_small(struct time_filter_small *tf, uint32_t incr_by, uint32_t now)
{
	int i;
	/* 
	 * Increase our filter main by incr_by and
	 * update its time. Then walk other's and
	 * make them the new value too.
	 */
	tf->entries[0].value += incr_by;
	tf->entries[0].time_up = now;
	for(i=1; i<NUM_FILTER_ENTRIES; i++) {
		tf->entries[i].value = tf->entries[0].value;
		tf->entries[i].time_up = now;
	}
}