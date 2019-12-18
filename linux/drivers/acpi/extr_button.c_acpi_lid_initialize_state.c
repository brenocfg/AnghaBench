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

/* Variables and functions */
#define  ACPI_BUTTON_LID_INIT_IGNORE 130 
#define  ACPI_BUTTON_LID_INIT_METHOD 129 
#define  ACPI_BUTTON_LID_INIT_OPEN 128 
 int /*<<< orphan*/  acpi_lid_notify_state (struct acpi_device*,int) ; 
 int /*<<< orphan*/  acpi_lid_update_state (struct acpi_device*,int) ; 
 int lid_init_state ; 

__attribute__((used)) static void acpi_lid_initialize_state(struct acpi_device *device)
{
	switch (lid_init_state) {
	case ACPI_BUTTON_LID_INIT_OPEN:
		(void)acpi_lid_notify_state(device, 1);
		break;
	case ACPI_BUTTON_LID_INIT_METHOD:
		(void)acpi_lid_update_state(device, false);
		break;
	case ACPI_BUTTON_LID_INIT_IGNORE:
	default:
		break;
	}
}