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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ NUMACHIP2_TIMER_DEADLINE ; 
 scalar_t__ numachip2_timer () ; 
 int /*<<< orphan*/  numachip2_write64_lcsr (scalar_t__,unsigned long) ; 

__attribute__((used)) static int numachip2_set_next_event(unsigned long delta, struct clock_event_device *ced)
{
	numachip2_write64_lcsr(NUMACHIP2_TIMER_DEADLINE + numachip2_timer(),
		delta);
	return 0;
}