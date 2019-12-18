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
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_EVENT_GLOBAL ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AE_NO_HARDWARE_RESPONSE ; 
 scalar_t__ AE_OK ; 
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  acpi_ev_global_lock_handler ; 
 void* acpi_gbl_global_lock_pending ; 
 int /*<<< orphan*/  acpi_gbl_global_lock_pending_lock ; 
 void* acpi_gbl_global_lock_present ; 
 scalar_t__ acpi_gbl_reduced_hardware ; 
 scalar_t__ acpi_install_fixed_event_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ acpi_os_create_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ev_init_global_lock_handler ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 

acpi_status acpi_ev_init_global_lock_handler(void)
{
	acpi_status status;

	ACPI_FUNCTION_TRACE(ev_init_global_lock_handler);

	/* If Hardware Reduced flag is set, there is no global lock */

	if (acpi_gbl_reduced_hardware) {
		return_ACPI_STATUS(AE_OK);
	}

	/* Attempt installation of the global lock handler */

	status = acpi_install_fixed_event_handler(ACPI_EVENT_GLOBAL,
						  acpi_ev_global_lock_handler,
						  NULL);

	/*
	 * If the global lock does not exist on this platform, the attempt to
	 * enable GBL_STATUS will fail (the GBL_ENABLE bit will not stick).
	 * Map to AE_OK, but mark global lock as not present. Any attempt to
	 * actually use the global lock will be flagged with an error.
	 */
	acpi_gbl_global_lock_present = FALSE;
	if (status == AE_NO_HARDWARE_RESPONSE) {
		ACPI_ERROR((AE_INFO,
			    "No response from Global Lock hardware, disabling lock"));

		return_ACPI_STATUS(AE_OK);
	}

	status = acpi_os_create_lock(&acpi_gbl_global_lock_pending_lock);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	acpi_gbl_global_lock_pending = FALSE;
	acpi_gbl_global_lock_present = TRUE;
	return_ACPI_STATUS(status);
}