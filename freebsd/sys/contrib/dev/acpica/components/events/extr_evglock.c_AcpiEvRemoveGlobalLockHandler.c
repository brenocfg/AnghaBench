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

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EVENT_GLOBAL ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiEvGlobalLockHandler ; 
 int /*<<< orphan*/  AcpiGbl_GlobalLockPendingLock ; 
 int /*<<< orphan*/  AcpiGbl_GlobalLockPresent ; 
 int /*<<< orphan*/  AcpiOsDeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiRemoveFixedEventHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EvRemoveGlobalLockHandler ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiEvRemoveGlobalLockHandler (
    void)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (EvRemoveGlobalLockHandler);


    AcpiGbl_GlobalLockPresent = FALSE;
    Status = AcpiRemoveFixedEventHandler (ACPI_EVENT_GLOBAL,
        AcpiEvGlobalLockHandler);

    AcpiOsDeleteLock (AcpiGbl_GlobalLockPendingLock);
    return_ACPI_STATUS (Status);
}