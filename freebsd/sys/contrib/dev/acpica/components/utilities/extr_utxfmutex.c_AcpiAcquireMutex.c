#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_4__ {int /*<<< orphan*/  OsMutex; } ;
struct TYPE_5__ {TYPE_1__ Mutex; } ;
typedef  int /*<<< orphan*/  ACPI_STRING ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsAcquireMutex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtGetMutexObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 

ACPI_STATUS
AcpiAcquireMutex (
    ACPI_HANDLE             Handle,
    ACPI_STRING             Pathname,
    UINT16                  Timeout)
{
    ACPI_STATUS             Status;
    ACPI_OPERAND_OBJECT     *MutexObj;


    /* Get the low-level mutex associated with Handle:Pathname */

    Status = AcpiUtGetMutexObject (Handle, Pathname, &MutexObj);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    /* Acquire the OS mutex */

    Status = AcpiOsAcquireMutex (MutexObj->Mutex.OsMutex, Timeout);
    return (Status);
}