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
 int /*<<< orphan*/  CVMX_IRQ_MBOX0 ; 
 int /*<<< orphan*/  cvmx_interrupt_unmask_irq (int /*<<< orphan*/ ) ; 

void cvmx_app_hotplug_shutdown_enable(void)
{
    cvmx_interrupt_unmask_irq(CVMX_IRQ_MBOX0);
}