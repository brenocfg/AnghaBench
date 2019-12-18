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
 scalar_t__ clockevent_state_oneshot (struct clock_event_device*) ; 
 int /*<<< orphan*/  mxs_irq_clear (char*) ; 
 int /*<<< orphan*/  timrot_irq_enable () ; 

__attribute__((used)) static int mxs_set_oneshot(struct clock_event_device *evt)
{
	if (clockevent_state_oneshot(evt))
		mxs_irq_clear("oneshot");
	timrot_irq_enable();
	return 0;
}