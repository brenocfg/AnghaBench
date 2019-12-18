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
 int /*<<< orphan*/  APM_DISABLED ; 
 int /*<<< orphan*/  APM_USER_SUSPEND ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  apm_queue_event (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t hp6x0_apm_interrupt(int irq, void *dev)
{
	if (!APM_DISABLED)
		apm_queue_event(APM_USER_SUSPEND);

	return IRQ_HANDLED;
}