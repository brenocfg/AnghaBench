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
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_3__ {int /*<<< orphan*/  OsMutex; } ;
struct TYPE_4__ {TYPE_1__ Mutex; } ;
typedef  void* BOOLEAN ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_CPU_FLAGS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ACQUIRE_GLOBAL_LOCK (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_WAIT_FOREVER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiExSystemWaitMutex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiExSystemWaitSemaphore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGbl_FACS ; 
 void* AcpiGbl_GlobalLockAcquired ; 
 int AcpiGbl_GlobalLockHandle ; 
 TYPE_2__* AcpiGbl_GlobalLockMutex ; 
 void* AcpiGbl_GlobalLockPending ; 
 int /*<<< orphan*/  AcpiGbl_GlobalLockPendingLock ; 
 int /*<<< orphan*/  AcpiGbl_GlobalLockPresent ; 
 int /*<<< orphan*/  AcpiGbl_GlobalLockSemaphore ; 
 int /*<<< orphan*/  AcpiOsAcquireLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsReleaseLock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EvAcquireGlobalLock ; 
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiEvAcquireGlobalLock (
    UINT16                  Timeout)
{
    ACPI_CPU_FLAGS          Flags;
    ACPI_STATUS             Status;
    BOOLEAN                 Acquired = FALSE;


    ACPI_FUNCTION_TRACE (EvAcquireGlobalLock);


    /*
     * Only one thread can acquire the GL at a time, the GlobalLockMutex
     * enforces this. This interface releases the interpreter if we must wait.
     */
    Status = AcpiExSystemWaitMutex (AcpiGbl_GlobalLockMutex->Mutex.OsMutex,
                Timeout);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /*
     * Update the global lock handle and check for wraparound. The handle is
     * only used for the external global lock interfaces, but it is updated
     * here to properly handle the case where a single thread may acquire the
     * lock via both the AML and the AcpiAcquireGlobalLock interfaces. The
     * handle is therefore updated on the first acquire from a given thread
     * regardless of where the acquisition request originated.
     */
    AcpiGbl_GlobalLockHandle++;
    if (AcpiGbl_GlobalLockHandle == 0)
    {
        AcpiGbl_GlobalLockHandle = 1;
    }

    /*
     * Make sure that a global lock actually exists. If not, just
     * treat the lock as a standard mutex.
     */
    if (!AcpiGbl_GlobalLockPresent)
    {
        AcpiGbl_GlobalLockAcquired = TRUE;
        return_ACPI_STATUS (AE_OK);
    }

    Flags = AcpiOsAcquireLock (AcpiGbl_GlobalLockPendingLock);

    do
    {
        /* Attempt to acquire the actual hardware lock */

        ACPI_ACQUIRE_GLOBAL_LOCK (AcpiGbl_FACS, Acquired);
        if (Acquired)
        {
            AcpiGbl_GlobalLockAcquired = TRUE;
            ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
                "Acquired hardware Global Lock\n"));
            break;
        }

        /*
         * Did not get the lock. The pending bit was set above, and
         * we must now wait until we receive the global lock
         * released interrupt.
         */
        AcpiGbl_GlobalLockPending = TRUE;
        AcpiOsReleaseLock (AcpiGbl_GlobalLockPendingLock, Flags);

        ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
            "Waiting for hardware Global Lock\n"));

        /*
         * Wait for handshake with the global lock interrupt handler.
         * This interface releases the interpreter if we must wait.
         */
        Status = AcpiExSystemWaitSemaphore (
            AcpiGbl_GlobalLockSemaphore, ACPI_WAIT_FOREVER);

        Flags = AcpiOsAcquireLock (AcpiGbl_GlobalLockPendingLock);

    } while (ACPI_SUCCESS (Status));

    AcpiGbl_GlobalLockPending = FALSE;
    AcpiOsReleaseLock (AcpiGbl_GlobalLockPendingLock, Flags);

    return_ACPI_STATUS (Status);
}