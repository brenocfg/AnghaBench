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
typedef  int uint32_t ;
struct time_filter_small {int cur_time_limit; TYPE_1__* entries; } ;
struct TYPE_2__ {int time_up; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int NUM_FILTER_ENTRIES ; 

void
tick_filter_clock_small(struct time_filter_small *tf, uint32_t now)
{
	int i;
	uint32_t tim, time_limit;

	/*
	 * We start at two positions back. This
	 * is because the oldest worst value is
	 * preserved always, i.e. it can't expire
	 * due to clock ticking with no updated value.
	 *
	 * The other choice would be to fill it in with
	 * zero, but I don't like that option since
	 * some measurement is better than none (even
	 * if its your oldest measurment).
	 */
	for(i=(NUM_FILTER_ENTRIES-2); i>=0 ; i--) {
		tim = now - tf->entries[i].time_up;
		time_limit = (tf->cur_time_limit * (NUM_FILTER_ENTRIES-i))/NUM_FILTER_ENTRIES;
		if (tim >= time_limit) {
			/* 
			 * This entry is expired, pull down
			 * the next one up.
			 */
			tf->entries[i].value = tf->entries[(i+1)].value;
			tf->entries[i].time_up = tf->entries[(i+1)].time_up;
		}

	}
}