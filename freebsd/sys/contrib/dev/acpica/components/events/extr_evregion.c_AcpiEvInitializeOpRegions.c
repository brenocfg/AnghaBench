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
typedef  size_t UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MTX_NAMESPACE ; 
 size_t ACPI_NUM_DEFAULT_SPACES ; 
 int /*<<< orphan*/  ACPI_REG_CONNECT ; 
 int /*<<< orphan*/  AcpiEvExecuteRegMethods (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ AcpiEvHasDefaultHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * AcpiGbl_DefaultAddressSpaces ; 
 int /*<<< orphan*/  AcpiGbl_RootNode ; 
 int /*<<< orphan*/  AcpiUtAcquireMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtReleaseMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EvInitializeOpRegions ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiEvInitializeOpRegions (
    void)
{
    ACPI_STATUS             Status;
    UINT32                  i;


    ACPI_FUNCTION_TRACE (EvInitializeOpRegions);


    Status = AcpiUtAcquireMutex (ACPI_MTX_NAMESPACE);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Run the _REG methods for OpRegions in each default address space */

    for (i = 0; i < ACPI_NUM_DEFAULT_SPACES; i++)
    {
        /*
         * Make sure the installed handler is the DEFAULT handler. If not the
         * default, the _REG methods will have already been run (when the
         * handler was installed)
         */
        if (AcpiEvHasDefaultHandler (AcpiGbl_RootNode,
               AcpiGbl_DefaultAddressSpaces[i]))
        {
            AcpiEvExecuteRegMethods (AcpiGbl_RootNode,
                AcpiGbl_DefaultAddressSpaces[i], ACPI_REG_CONNECT);
        }
    }

    (void) AcpiUtReleaseMutex (ACPI_MTX_NAMESPACE);
    return_ACPI_STATUS (Status);
}