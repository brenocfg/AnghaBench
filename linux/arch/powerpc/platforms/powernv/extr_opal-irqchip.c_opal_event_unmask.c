#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct TYPE_2__ {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 TYPE_1__ opal_event_irqchip ; 
 scalar_t__ opal_have_pending_events () ; 
 int /*<<< orphan*/  opal_wake_poller () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void opal_event_unmask(struct irq_data *d)
{
	set_bit(d->hwirq, &opal_event_irqchip.mask);
	if (opal_have_pending_events())
		opal_wake_poller();
}