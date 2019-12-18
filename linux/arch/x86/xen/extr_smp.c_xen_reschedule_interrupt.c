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

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_resched_count ; 
 int /*<<< orphan*/  scheduler_ipi () ; 

__attribute__((used)) static irqreturn_t xen_reschedule_interrupt(int irq, void *dev_id)
{
	inc_irq_stat(irq_resched_count);
	scheduler_ipi();

	return IRQ_HANDLED;
}