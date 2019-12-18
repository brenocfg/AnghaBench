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
 int /*<<< orphan*/  pm_system_wakeup () ; 
 unsigned int pm_wakeup_irq ; 

void pm_system_irq_wakeup(unsigned int irq_number)
{
	if (pm_wakeup_irq == 0) {
		pm_wakeup_irq = irq_number;
		pm_system_wakeup();
	}
}