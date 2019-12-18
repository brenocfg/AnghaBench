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
typedef  int UINT32 ;
struct TYPE_4__ {struct TYPE_4__* Next; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  size_t ACPI_SIZE ;

/* Variables and functions */
 int ACPI_ARRAY_LENGTH (TYPE_1__*) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_WAIT_FOREVER ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_1__* AcpiDefaultSupportedInterfaces ; 
 int /*<<< orphan*/  AcpiGbl_OsiMutex ; 
 TYPE_1__* AcpiGbl_SupportedInterfaces ; 
 int /*<<< orphan*/  AcpiOsAcquireMutex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsReleaseMutex (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiUtInitializeInterfaces (
    void)
{
    ACPI_STATUS             Status;
    UINT32                  i;


    Status = AcpiOsAcquireMutex (AcpiGbl_OsiMutex, ACPI_WAIT_FOREVER);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    AcpiGbl_SupportedInterfaces = AcpiDefaultSupportedInterfaces;

    /* Link the static list of supported interfaces */

    for (i = 0;
        i < (ACPI_ARRAY_LENGTH (AcpiDefaultSupportedInterfaces) - 1);
        i++)
    {
        AcpiDefaultSupportedInterfaces[i].Next =
            &AcpiDefaultSupportedInterfaces[(ACPI_SIZE) i + 1];
    }

    AcpiOsReleaseMutex (AcpiGbl_OsiMutex);
    return (AE_OK);
}