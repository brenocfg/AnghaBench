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
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INIT ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/  (*) ()) ; 
 scalar_t__ ACPI_INVALID_TABLE_INDEX ; 
 scalar_t__ ACPI_SYS_MODE_ACPI ; 
 int /*<<< orphan*/  ACPI_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_ACPI_TABLES ; 
 int /*<<< orphan*/  AE_NO_HARDWARE_RESPONSE ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ acpi_gbl_fadt_index ; 
 scalar_t__ acpi_gbl_reduced_hardware ; 
 scalar_t__ acpi_hw_get_mode () ; 
 int /*<<< orphan*/  acpi_hw_set_mode (scalar_t__) ; 
 int /*<<< orphan*/  acpi_os_stall (int) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_enable(void)
{
	acpi_status status;
	int retry;

	ACPI_FUNCTION_TRACE(acpi_enable);

	/* ACPI tables must be present */

	if (acpi_gbl_fadt_index == ACPI_INVALID_TABLE_INDEX) {
		return_ACPI_STATUS(AE_NO_ACPI_TABLES);
	}

	/* If the Hardware Reduced flag is set, machine is always in acpi mode */

	if (acpi_gbl_reduced_hardware) {
		return_ACPI_STATUS(AE_OK);
	}

	/* Check current mode */

	if (acpi_hw_get_mode() == ACPI_SYS_MODE_ACPI) {
		ACPI_DEBUG_PRINT((ACPI_DB_INIT,
				  "System is already in ACPI mode\n"));
		return_ACPI_STATUS(AE_OK);
	}

	/* Transition to ACPI mode */

	status = acpi_hw_set_mode(ACPI_SYS_MODE_ACPI);
	if (ACPI_FAILURE(status)) {
		ACPI_ERROR((AE_INFO,
			    "Could not transition to ACPI mode"));
		return_ACPI_STATUS(status);
	}

	/* Sanity check that transition succeeded */

	for (retry = 0; retry < 30000; ++retry) {
		if (acpi_hw_get_mode() == ACPI_SYS_MODE_ACPI) {
			if (retry != 0)
				ACPI_WARNING((AE_INFO,
				"Platform took > %d00 usec to enter ACPI mode", retry));
			return_ACPI_STATUS(AE_OK);
		}
		acpi_os_stall(100);	/* 100 usec */
	}

	ACPI_ERROR((AE_INFO, "Hardware did not enter ACPI mode"));
	return_ACPI_STATUS(AE_NO_HARDWARE_RESPONSE);
}