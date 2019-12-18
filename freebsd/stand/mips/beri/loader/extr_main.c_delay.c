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
typedef  int uint32_t ;

/* Variables and functions */
 int cp0_count_get () ; 

void
delay(int usecs)
{
	uint32_t delta;
	uint32_t curr;
	uint32_t last;

	last = cp0_count_get();
	while (usecs > 0) {
		curr = cp0_count_get();
		delta = curr - last;
		while (usecs > 0 && delta >= 100) {
			usecs--;
			last += 100;
			delta -= 100;
		}
	}
}