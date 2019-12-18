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
struct input_dev {int dummy; } ;
struct acpi_device {int dummy; } ;
struct acpi_button {int last_state; int /*<<< orphan*/  last_time; } ;

/* Variables and functions */
 struct acpi_button* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_lid_evaluate_state (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_lid_initialize_state (struct acpi_device*) ; 
 struct acpi_device* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  ktime_get () ; 

__attribute__((used)) static int acpi_lid_input_open(struct input_dev *input)
{
	struct acpi_device *device = input_get_drvdata(input);
	struct acpi_button *button = acpi_driver_data(device);

	button->last_state = !!acpi_lid_evaluate_state(device);
	button->last_time = ktime_get();
	acpi_lid_initialize_state(device);

	return 0;
}