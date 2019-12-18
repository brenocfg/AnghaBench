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
 int /*<<< orphan*/  acpi_sci_irq ; 
 scalar_t__ acpi_sci_irq_valid () ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kacpi_notify_wq ; 
 int /*<<< orphan*/  kacpid_wq ; 
 int /*<<< orphan*/  synchronize_hardirq (int /*<<< orphan*/ ) ; 

void acpi_os_wait_events_complete(void)
{
	/*
	 * Make sure the GPE handler or the fixed event handler is not used
	 * on another CPU after removal.
	 */
	if (acpi_sci_irq_valid())
		synchronize_hardirq(acpi_sci_irq);
	flush_workqueue(kacpid_wq);
	flush_workqueue(kacpi_notify_wq);
}