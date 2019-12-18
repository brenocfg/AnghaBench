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
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ LCL_TIMER_EVENTS_STATUS ; 
 int /*<<< orphan*/  TIMER0_CLR_MASK ; 
 scalar_t__ local_base ; 
 int /*<<< orphan*/  stub1 (struct clock_event_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t armada_370_xp_timer_interrupt(int irq, void *dev_id)
{
	/*
	 * ACK timer interrupt and call event handler.
	 */
	struct clock_event_device *evt = dev_id;

	writel(TIMER0_CLR_MASK, local_base + LCL_TIMER_EVENTS_STATUS);
	evt->event_handler(evt);

	return IRQ_HANDLED;
}