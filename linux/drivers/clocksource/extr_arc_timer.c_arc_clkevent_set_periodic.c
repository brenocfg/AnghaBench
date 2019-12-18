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
 int HZ ; 
 int /*<<< orphan*/  arc_timer_event_setup (int) ; 
 int arc_timer_freq ; 

__attribute__((used)) static int arc_clkevent_set_periodic(struct clock_event_device *dev)
{
	/*
	 * At X Hz, 1 sec = 1000ms -> X cycles;
	 *		      10ms -> X / 100 cycles
	 */
	arc_timer_event_setup(arc_timer_freq / HZ);
	return 0;
}