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
typedef  int u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int /*<<< orphan*/  acpi_disable; int /*<<< orphan*/  smi_command; int /*<<< orphan*/  acpi_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
#define  ACPI_SYS_MODE_ACPI 129 
#define  ACPI_SYS_MODE_LEGACY 128 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_HARDWARE_RESPONSE ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_1__ acpi_gbl_FADT ; 
 scalar_t__ acpi_gbl_reduced_hardware ; 
 int /*<<< orphan*/  acpi_hw_write_port (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  hw_set_mode ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_hw_set_mode(u32 mode)
{

	acpi_status status;

	ACPI_FUNCTION_TRACE(hw_set_mode);

	/* If the Hardware Reduced flag is set, machine is always in acpi mode */

	if (acpi_gbl_reduced_hardware) {
		return_ACPI_STATUS(AE_OK);
	}

	/*
	 * ACPI 2.0 clarified that if SMI_CMD in FADT is zero,
	 * system does not support mode transition.
	 */
	if (!acpi_gbl_FADT.smi_command) {
		ACPI_ERROR((AE_INFO,
			    "No SMI_CMD in FADT, mode transition failed"));
		return_ACPI_STATUS(AE_NO_HARDWARE_RESPONSE);
	}

	/*
	 * ACPI 2.0 clarified the meaning of ACPI_ENABLE and ACPI_DISABLE
	 * in FADT: If it is zero, enabling or disabling is not supported.
	 * As old systems may have used zero for mode transition,
	 * we make sure both the numbers are zero to determine these
	 * transitions are not supported.
	 */
	if (!acpi_gbl_FADT.acpi_enable && !acpi_gbl_FADT.acpi_disable) {
		ACPI_ERROR((AE_INFO,
			    "No ACPI mode transition supported in this system "
			    "(enable/disable both zero)"));
		return_ACPI_STATUS(AE_OK);
	}

	switch (mode) {
	case ACPI_SYS_MODE_ACPI:

		/* BIOS should have disabled ALL fixed and GP events */

		status = acpi_hw_write_port(acpi_gbl_FADT.smi_command,
					    (u32) acpi_gbl_FADT.acpi_enable, 8);
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "Attempting to enable ACPI mode\n"));
		break;

	case ACPI_SYS_MODE_LEGACY:
		/*
		 * BIOS should clear all fixed status bits and restore fixed event
		 * enable bits to default
		 */
		status = acpi_hw_write_port(acpi_gbl_FADT.smi_command,
					    (u32)acpi_gbl_FADT.acpi_disable, 8);
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "Attempting to enable Legacy (non-ACPI) mode\n"));
		break;

	default:

		return_ACPI_STATUS(AE_BAD_PARAMETER);
	}

	if (ACPI_FAILURE(status)) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Could not write ACPI mode change"));
		return_ACPI_STATUS(status);
	}

	return_ACPI_STATUS(AE_OK);
}