#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_4__ {int Length; int Version; scalar_t__ XFirmwareWakingVector; scalar_t__ FirmwareWakingVector; } ;
typedef  TYPE_1__ ACPI_TABLE_FACS ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  scalar_t__ ACPI_PHYSICAL_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/  (*) (TYPE_1__*,scalar_t__,scalar_t__)) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AcpiHwSetFirmwareWakingVector (
    ACPI_TABLE_FACS         *Facs,
    ACPI_PHYSICAL_ADDRESS   PhysicalAddress,
    ACPI_PHYSICAL_ADDRESS   PhysicalAddress64)
{
    ACPI_FUNCTION_TRACE (AcpiHwSetFirmwareWakingVector);


    /*
     * According to the ACPI specification 2.0c and later, the 64-bit
     * waking vector should be cleared and the 32-bit waking vector should
     * be used, unless we want the wake-up code to be called by the BIOS in
     * Protected Mode. Some systems (for example HP dv5-1004nr) are known
     * to fail to resume if the 64-bit vector is used.
     */

    /* Set the 32-bit vector */

    Facs->FirmwareWakingVector = (UINT32) PhysicalAddress;

    if (Facs->Length > 32)
    {
        if (Facs->Version >= 1)
        {
            /* Set the 64-bit vector */

            Facs->XFirmwareWakingVector = PhysicalAddress64;
        }
        else
        {
            /* Clear the 64-bit vector if it exists */

            Facs->XFirmwareWakingVector = 0;
        }
    }

    return_ACPI_STATUS (AE_OK);
}