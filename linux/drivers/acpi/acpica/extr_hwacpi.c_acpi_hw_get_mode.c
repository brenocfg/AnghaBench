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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int /*<<< orphan*/  smi_command; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BITREG_SCI_ENABLE ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SYS_MODE_ACPI ; 
 int /*<<< orphan*/  ACPI_SYS_MODE_LEGACY ; 
 TYPE_1__ acpi_gbl_FADT ; 
 scalar_t__ acpi_gbl_reduced_hardware ; 
 int /*<<< orphan*/  acpi_read_bit_register (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  hw_get_mode ; 
 int /*<<< orphan*/  return_UINT32 (int /*<<< orphan*/ ) ; 

u32 acpi_hw_get_mode(void)
{
	acpi_status status;
	u32 value;

	ACPI_FUNCTION_TRACE(hw_get_mode);

	/* If the Hardware Reduced flag is set, machine is always in acpi mode */

	if (acpi_gbl_reduced_hardware) {
		return_UINT32(ACPI_SYS_MODE_ACPI);
	}

	/*
	 * ACPI 2.0 clarified that if SMI_CMD in FADT is zero,
	 * system does not support mode transition.
	 */
	if (!acpi_gbl_FADT.smi_command) {
		return_UINT32(ACPI_SYS_MODE_ACPI);
	}

	status = acpi_read_bit_register(ACPI_BITREG_SCI_ENABLE, &value);
	if (ACPI_FAILURE(status)) {
		return_UINT32(ACPI_SYS_MODE_LEGACY);
	}

	if (value) {
		return_UINT32(ACPI_SYS_MODE_ACPI);
	} else {
		return_UINT32(ACPI_SYS_MODE_LEGACY);
	}
}