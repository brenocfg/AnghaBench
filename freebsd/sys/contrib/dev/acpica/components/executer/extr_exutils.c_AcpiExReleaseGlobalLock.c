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
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int AML_FIELD_LOCK_RULE_MASK ; 
 int /*<<< orphan*/  AcpiExReleaseMutexObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGbl_GlobalLockMutex ; 
 int /*<<< orphan*/  ExReleaseGlobalLock ; 
 int /*<<< orphan*/  return_VOID ; 

void
AcpiExReleaseGlobalLock (
    UINT32                  FieldFlags)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (ExReleaseGlobalLock);


    /* Only use the lock if the AlwaysLock bit is set */

    if (!(FieldFlags & AML_FIELD_LOCK_RULE_MASK))
    {
        return_VOID;
    }

    /* Release the global lock */

    Status = AcpiExReleaseMutexObject (AcpiGbl_GlobalLockMutex);
    if (ACPI_FAILURE (Status))
    {
        /* Report the error, but there isn't much else we can do */

        ACPI_EXCEPTION ((AE_INFO, Status,
            "Could not release Global Lock"));
    }

    return_VOID;
}