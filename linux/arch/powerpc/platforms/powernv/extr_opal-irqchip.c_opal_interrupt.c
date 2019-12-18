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
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  last_outstanding_events ; 
 int /*<<< orphan*/  opal_handle_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ opal_have_pending_events () ; 
 int /*<<< orphan*/  opal_wake_poller () ; 
 int /*<<< orphan*/  virq_to_hw (int) ; 

__attribute__((used)) static irqreturn_t opal_interrupt(int irq, void *data)
{
	__be64 events;

	opal_handle_interrupt(virq_to_hw(irq), &events);
	last_outstanding_events = be64_to_cpu(events);
	if (opal_have_pending_events())
		opal_wake_poller();

	return IRQ_HANDLED;
}