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
struct clock_event_device {int /*<<< orphan*/  (* event_handler ) (struct clock_event_device*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__* CSR_TIMER1_CLR ; 
 scalar_t__* CSR_TIMER1_CNTL ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ clockevent_state_oneshot (struct clock_event_device*) ; 
 int /*<<< orphan*/  stub1 (struct clock_event_device*) ; 

__attribute__((used)) static irqreturn_t timer1_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *ce = dev_id;

	*CSR_TIMER1_CLR = 0;

	/* Stop the timer if in one-shot mode */
	if (clockevent_state_oneshot(ce))
		*CSR_TIMER1_CNTL = 0;

	ce->event_handler(ce);

	return IRQ_HANDLED;
}