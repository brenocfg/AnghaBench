#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  OsMutex; } ;
struct TYPE_4__ {TYPE_1__ Mutex; } ;
typedef  void* BOOLEAN ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BITREG_GLOBAL_LOCK_RELEASE ; 
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ENABLE_EVENT ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_RELEASE_GLOBAL_LOCK (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ACPI_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NOT_ACQUIRED ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiGbl_FACS ; 
 void* AcpiGbl_GlobalLockAcquired ; 
 TYPE_2__* AcpiGbl_GlobalLockMutex ; 
 scalar_t__ AcpiGbl_GlobalLockPresent ; 
 int /*<<< orphan*/  AcpiOsReleaseMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiWriteBitRegister (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EvReleaseGlobalLock ; 
 void* FALSE ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiEvReleaseGlobalLock (
    void)
{
    BOOLEAN                 Pending = FALSE;
    ACPI_STATUS             Status = AE_OK;


    ACPI_FUNCTION_TRACE (EvReleaseGlobalLock);


    /* Lock must be already acquired */

    if (!AcpiGbl_GlobalLockAcquired)
    {
        ACPI_WARNING ((AE_INFO,
            "Cannot release the ACPI Global Lock, it has not been acquired"));
        return_ACPI_STATUS (AE_NOT_ACQUIRED);
    }

    if (AcpiGbl_GlobalLockPresent)
    {
        /* Allow any thread to release the lock */

        ACPI_RELEASE_GLOBAL_LOCK (AcpiGbl_FACS, Pending);

        /*
         * If the pending bit was set, we must write GBL_RLS to the control
         * register
         */
        if (Pending)
        {
            Status = AcpiWriteBitRegister (
                ACPI_BITREG_GLOBAL_LOCK_RELEASE, ACPI_ENABLE_EVENT);
        }

        ACPI_DEBUG_PRINT ((ACPI_DB_EXEC, "Released hardware Global Lock\n"));
    }

    AcpiGbl_GlobalLockAcquired = FALSE;

    /* Release the local GL mutex */

    AcpiOsReleaseMutex (AcpiGbl_GlobalLockMutex->Mutex.OsMutex);
    return_ACPI_STATUS (Status);
}