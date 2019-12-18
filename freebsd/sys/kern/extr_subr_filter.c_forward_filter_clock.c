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
struct time_filter {TYPE_1__* entries; } ;
struct TYPE_2__ {int /*<<< orphan*/  time_up; } ;

/* Variables and functions */
 int NUM_FILTER_ENTRIES ; 

void
forward_filter_clock(struct time_filter *tf, uint32_t ticks_forward)
{
	/*
	 * Bring forward all time values by N ticks. This
	 * postpones expiring slots by that amount.
	 */
	int i;

	for(i=0; i<NUM_FILTER_ENTRIES; i++) {
		tf->entries[i].time_up += ticks_forward;
	}
}