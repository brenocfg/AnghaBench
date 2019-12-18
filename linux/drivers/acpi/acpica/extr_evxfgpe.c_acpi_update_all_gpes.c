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
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/  (*) ()) ; 
 int /*<<< orphan*/  ACPI_MTX_EVENTS ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  acpi_ev_gpe_detect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ev_initialize_gpe_block ; 
 int /*<<< orphan*/  acpi_ev_walk_gpe_list (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ acpi_gbl_all_gpes_initialized ; 
 int /*<<< orphan*/  acpi_gbl_gpe_xrupt_list_head ; 
 int /*<<< orphan*/  acpi_ut_acquire_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_release_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_update_all_gpes(void)
{
	acpi_status status;
	u8 is_polling_needed = FALSE;

	ACPI_FUNCTION_TRACE(acpi_update_all_gpes);

	status = acpi_ut_acquire_mutex(ACPI_MTX_EVENTS);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	if (acpi_gbl_all_gpes_initialized) {
		goto unlock_and_exit;
	}

	status = acpi_ev_walk_gpe_list(acpi_ev_initialize_gpe_block,
				       &is_polling_needed);
	if (ACPI_SUCCESS(status)) {
		acpi_gbl_all_gpes_initialized = TRUE;
	}

unlock_and_exit:
	(void)acpi_ut_release_mutex(ACPI_MTX_EVENTS);

	if (is_polling_needed && acpi_gbl_all_gpes_initialized) {

		/* Poll GPEs to handle already triggered events */

		acpi_ev_gpe_detect(acpi_gbl_gpe_xrupt_list_head);
	}
	return_ACPI_STATUS(status);
}