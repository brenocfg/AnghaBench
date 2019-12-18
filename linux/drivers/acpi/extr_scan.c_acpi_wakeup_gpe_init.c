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
struct TYPE_2__ {scalar_t__ notifier_present; } ;
struct acpi_device_wakeup {scalar_t__ sleep_state; int /*<<< orphan*/  gpe_number; int /*<<< orphan*/  gpe_device; TYPE_1__ flags; } ;
struct acpi_device_id {char* member_0; int /*<<< orphan*/  member_1; } ;
struct acpi_device {int /*<<< orphan*/  handle; int /*<<< orphan*/  dev; struct acpi_device_wakeup wakeup; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_STATE_S4 ; 
 scalar_t__ ACPI_STATE_S5 ; 
 int ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_mark_gpe_for_wake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_match_device_ids (struct acpi_device*,struct acpi_device_id const*) ; 
 int /*<<< orphan*/  acpi_setup_gpe_for_wake (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool acpi_wakeup_gpe_init(struct acpi_device *device)
{
	static const struct acpi_device_id button_device_ids[] = {
		{"PNP0C0C", 0},		/* Power button */
		{"PNP0C0D", 0},		/* Lid */
		{"PNP0C0E", 0},		/* Sleep button */
		{"", 0},
	};
	struct acpi_device_wakeup *wakeup = &device->wakeup;
	acpi_status status;

	wakeup->flags.notifier_present = 0;

	/* Power button, Lid switch always enable wakeup */
	if (!acpi_match_device_ids(device, button_device_ids)) {
		if (!acpi_match_device_ids(device, &button_device_ids[1])) {
			/* Do not use Lid/sleep button for S5 wakeup */
			if (wakeup->sleep_state == ACPI_STATE_S5)
				wakeup->sleep_state = ACPI_STATE_S4;
		}
		acpi_mark_gpe_for_wake(wakeup->gpe_device, wakeup->gpe_number);
		device_set_wakeup_capable(&device->dev, true);
		return true;
	}

	status = acpi_setup_gpe_for_wake(device->handle, wakeup->gpe_device,
					 wakeup->gpe_number);
	return ACPI_SUCCESS(status);
}