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
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ SIRFSOC_TIMER_INTR_STATUS ; 
 scalar_t__ clockevent_state_oneshot (struct clock_event_device*) ; 
 scalar_t__ sirfsoc_timer_base ; 
 int /*<<< orphan*/  sirfsoc_timer_count_disable (int) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  stub1 (struct clock_event_device*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t sirfsoc_timer_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *ce = dev_id;
	int cpu = smp_processor_id();

	/* clear timer interrupt */
	writel_relaxed(BIT(cpu), sirfsoc_timer_base + SIRFSOC_TIMER_INTR_STATUS);

	if (clockevent_state_oneshot(ce))
		sirfsoc_timer_count_disable(cpu);

	ce->event_handler(ce);

	return IRQ_HANDLED;
}