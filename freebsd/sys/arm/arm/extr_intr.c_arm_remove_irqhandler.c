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
struct intr_event {int /*<<< orphan*/  ie_handlers; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arm_mask_irq (int) ; 
 int /*<<< orphan*/  arm_unmask_irq (int) ; 
 int intr_event_remove_handler (void*) ; 
 struct intr_event** intr_events ; 

int
arm_remove_irqhandler(int irq, void *cookie)
{
	struct intr_event *event;
	int error;

	event = intr_events[irq];
	arm_mask_irq(irq);

	error = intr_event_remove_handler(cookie);

	if (!CK_SLIST_EMPTY(&event->ie_handlers))
		arm_unmask_irq(irq);
	return (error);
}