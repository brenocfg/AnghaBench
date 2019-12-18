#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ delay_fn ; 
 scalar_t__ delay_tsc ; 
 unsigned long rdtsc () ; 

int read_current_timer(unsigned long *timer_val)
{
	if (delay_fn == delay_tsc) {
		*timer_val = rdtsc();
		return 0;
	}
	return -1;
}