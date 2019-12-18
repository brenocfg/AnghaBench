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
typedef  scalar_t__ u8 ;
struct acpi_gpe_event_info {int runtime_count; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int ACPI_UINT8_MAX ; 
 int /*<<< orphan*/  AE_LIMIT ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ev_enable_gpe (struct acpi_gpe_event_info*) ; 
 int /*<<< orphan*/  acpi_ev_update_gpe_enable_mask (struct acpi_gpe_event_info*) ; 
 int /*<<< orphan*/  acpi_hw_clear_gpe (struct acpi_gpe_event_info*) ; 
 int /*<<< orphan*/  ev_add_gpe_reference ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ev_add_gpe_reference(struct acpi_gpe_event_info *gpe_event_info,
			  u8 clear_on_enable)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ev_add_gpe_reference);

	if (gpe_event_info->runtime_count == ACPI_UINT8_MAX) {
		return_ACPI_STATUS(AE_LIMIT);
	}

	gpe_event_info->runtime_count++;
	if (gpe_event_info->runtime_count == 1) {

		/* Enable on first reference */

		if (clear_on_enable) {
			(void)acpi_hw_clear_gpe(gpe_event_info);
		}

		status = acpi_ev_update_gpe_enable_mask(gpe_event_info);
		if (ACPI_SUCCESS(status)) {
			status = acpi_ev_enable_gpe(gpe_event_info);
		}

		if (ACPI_FAILURE(status)) {
			gpe_event_info->runtime_count--;
		}
	}

	return_ACPI_STATUS(status);
}