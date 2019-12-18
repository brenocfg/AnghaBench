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
struct acpi_ipmi_device {int dead; int /*<<< orphan*/  head; } ;
struct TYPE_2__ {struct acpi_ipmi_device* selected_smi; } ;

/* Variables and functions */
 TYPE_1__ driver_data ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __ipmi_dev_kill(struct acpi_ipmi_device *ipmi_device)
{
	list_del(&ipmi_device->head);
	if (driver_data.selected_smi == ipmi_device)
		driver_data.selected_smi = NULL;

	/*
	 * Always setting dead flag after deleting from the list or
	 * list_for_each_entry() codes must get changed.
	 */
	ipmi_device->dead = true;
}