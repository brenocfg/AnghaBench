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
typedef  int /*<<< orphan*/  acpi_physical_address ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ acpi_gbl_FACS ; 
 int /*<<< orphan*/  acpi_hw_set_firmware_waking_vector (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_set_firmware_waking_vector(acpi_physical_address physical_address,
				acpi_physical_address physical_address64)
{

	ACPI_FUNCTION_TRACE(acpi_set_firmware_waking_vector);

	if (acpi_gbl_FACS) {
		(void)acpi_hw_set_firmware_waking_vector(acpi_gbl_FACS,
							 physical_address,
							 physical_address64);
	}

	return_ACPI_STATUS(AE_OK);
}