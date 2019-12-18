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
struct timer_of {int dummy; } ;
struct clock_event_device {int /*<<< orphan*/  (* event_handler ) (struct clock_event_device*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ RDA_TIMER_IRQ_CLR ; 
 int /*<<< orphan*/  RDA_TIMER_IRQ_CLR_OSTIMER ; 
 int /*<<< orphan*/  stub1 (struct clock_event_device*) ; 
 scalar_t__ timer_of_base (struct timer_of*) ; 
 struct timer_of* to_timer_of (struct clock_event_device*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t rda_ostimer_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *evt = dev_id;
	struct timer_of *to = to_timer_of(evt);

	/* clear timer int */
	writel_relaxed(RDA_TIMER_IRQ_CLR_OSTIMER,
		       timer_of_base(to) + RDA_TIMER_IRQ_CLR);

	if (evt->event_handler)
		evt->event_handler(evt);

	return IRQ_HANDLED;
}