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
struct TYPE_2__ {int /*<<< orphan*/  Address; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_CPU_FLAGS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BITMASK_ALL_FIXED_STATUS ; 
 int /*<<< orphan*/  ACPI_DB_IO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_REGISTER_PM1_STATUS ; 
 int /*<<< orphan*/  AcpiEvWalkGpeList (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiGbl_HardwareLock ; 
 TYPE_1__ AcpiGbl_XPm1aStatus ; 
 int /*<<< orphan*/  AcpiHwClearGpeBlock ; 
 int /*<<< orphan*/  AcpiHwRegisterWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsAcquireLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsReleaseLock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HwClearAcpiStatus ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiHwClearAcpiStatus (
    void)
{
    ACPI_STATUS             Status;
    ACPI_CPU_FLAGS          LockFlags = 0;


    ACPI_FUNCTION_TRACE (HwClearAcpiStatus);


    ACPI_DEBUG_PRINT ((ACPI_DB_IO, "About to write %04X to %8.8X%8.8X\n",
        ACPI_BITMASK_ALL_FIXED_STATUS,
        ACPI_FORMAT_UINT64 (AcpiGbl_XPm1aStatus.Address)));

    LockFlags = AcpiOsAcquireLock (AcpiGbl_HardwareLock);

    /* Clear the fixed events in PM1 A/B */

    Status = AcpiHwRegisterWrite (ACPI_REGISTER_PM1_STATUS,
        ACPI_BITMASK_ALL_FIXED_STATUS);

    AcpiOsReleaseLock (AcpiGbl_HardwareLock, LockFlags);

    if (ACPI_FAILURE (Status))
    {
        goto Exit;
    }

    /* Clear the GPE Bits in all GPE registers in all GPE blocks */

    Status = AcpiEvWalkGpeList (AcpiHwClearGpeBlock, NULL);

Exit:
    return_ACPI_STATUS (Status);
}