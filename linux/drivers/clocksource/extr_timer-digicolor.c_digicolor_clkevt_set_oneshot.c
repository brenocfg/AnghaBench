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
 int /*<<< orphan*/  CONTROL_MODE_ONESHOT ; 
 int /*<<< orphan*/  dc_timer_disable (struct clock_event_device*) ; 
 int /*<<< orphan*/  dc_timer_enable (struct clock_event_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int digicolor_clkevt_set_oneshot(struct clock_event_device *ce)
{
	dc_timer_disable(ce);
	dc_timer_enable(ce, CONTROL_MODE_ONESHOT);
	return 0;
}