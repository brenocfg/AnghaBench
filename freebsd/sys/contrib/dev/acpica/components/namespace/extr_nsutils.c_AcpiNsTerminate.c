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
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MTX_NAMESPACE ; 
 int /*<<< orphan*/  AcpiGbl_RootNode ; 
 int /*<<< orphan*/  AcpiNsDeleteNamespaceSubtree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiNsDeleteNode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtAcquireMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtReleaseMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NsTerminate ; 
 int /*<<< orphan*/  return_VOID ; 

void
AcpiNsTerminate (
    void)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (NsTerminate);


    /*
     * Free the entire namespace -- all nodes and all objects
     * attached to the nodes
     */
    AcpiNsDeleteNamespaceSubtree (AcpiGbl_RootNode);

    /* Delete any objects attached to the root node */

    Status = AcpiUtAcquireMutex (ACPI_MTX_NAMESPACE);
    if (ACPI_FAILURE (Status))
    {
        return_VOID;
    }

    AcpiNsDeleteNode (AcpiGbl_RootNode);
    (void) AcpiUtReleaseMutex (ACPI_MTX_NAMESPACE);

    ACPI_DEBUG_PRINT ((ACPI_DB_INFO, "Namespace freed\n"));
    return_VOID;
}