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
struct acpi_device {int dummy; } ;
struct acpi_button {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_button_remove_fs (struct acpi_device*) ; 
 struct acpi_button* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct acpi_button*) ; 

__attribute__((used)) static int acpi_button_remove(struct acpi_device *device)
{
	struct acpi_button *button = acpi_driver_data(device);

	acpi_button_remove_fs(device);
	input_unregister_device(button->input);
	kfree(button);
	return 0;
}