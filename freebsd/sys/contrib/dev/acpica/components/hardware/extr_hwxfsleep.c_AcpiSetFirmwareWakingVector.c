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
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_PHYSICAL_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ AcpiGbl_FACS ; 
 int /*<<< orphan*/  AcpiHwSetFirmwareWakingVector (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiSetFirmwareWakingVector (
    ACPI_PHYSICAL_ADDRESS   PhysicalAddress,
    ACPI_PHYSICAL_ADDRESS   PhysicalAddress64)
{

    ACPI_FUNCTION_TRACE (AcpiSetFirmwareWakingVector);

    if (AcpiGbl_FACS)
    {
        (void) AcpiHwSetFirmwareWakingVector (AcpiGbl_FACS,
            PhysicalAddress, PhysicalAddress64);
    }

    return_ACPI_STATUS (AE_OK);
}