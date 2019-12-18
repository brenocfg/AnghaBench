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

/* Variables and functions */
 int /*<<< orphan*/  __cpu_do_idle () ; 
 int /*<<< orphan*/  __cpu_do_idle_irqprio () ; 
 scalar_t__ system_uses_irq_prio_masking () ; 

void cpu_do_idle(void)
{
	if (system_uses_irq_prio_masking())
		__cpu_do_idle_irqprio();
	else
		__cpu_do_idle();
}