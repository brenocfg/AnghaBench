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
struct acpi_smb_hc {int /*<<< orphan*/  lock; int /*<<< orphan*/ * context; int /*<<< orphan*/ * callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_os_wait_events_complete () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int acpi_smbus_unregister_callback(struct acpi_smb_hc *hc)
{
	mutex_lock(&hc->lock);
	hc->callback = NULL;
	hc->context = NULL;
	mutex_unlock(&hc->lock);
	acpi_os_wait_events_complete();
	return 0;
}