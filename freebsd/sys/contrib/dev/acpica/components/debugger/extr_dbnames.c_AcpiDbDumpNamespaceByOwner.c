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
typedef  scalar_t__ UINT32 ;
typedef  scalar_t__ ACPI_OWNER_ID ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_CONSOLE_OUTPUT ; 
 int /*<<< orphan*/  ACPI_DB_DUPLICATE_OUTPUT ; 
 int /*<<< orphan*/  ACPI_DB_REDIRECTABLE_OUTPUT ; 
 int /*<<< orphan*/  ACPI_DISPLAY_SUMMARY ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 scalar_t__ ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AcpiDbSetOutputDestination (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGbl_RootNode ; 
 int /*<<< orphan*/  AcpiNsDumpObjects (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,scalar_t__) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
AcpiDbDumpNamespaceByOwner (
    char                    *OwnerArg,
    char                    *DepthArg)
{
    ACPI_HANDLE             SubtreeEntry = AcpiGbl_RootNode;
    UINT32                  MaxDepth = ACPI_UINT32_MAX;
    ACPI_OWNER_ID           OwnerId;


    OwnerId = (ACPI_OWNER_ID) strtoul (OwnerArg, NULL, 0);

    /* Now we can check for the depth argument */

    if (DepthArg)
    {
        MaxDepth = strtoul (DepthArg, NULL, 0);
    }

    AcpiDbSetOutputDestination (ACPI_DB_DUPLICATE_OUTPUT);
    AcpiOsPrintf ("ACPI Namespace by owner %X:\n", OwnerId);

    /* Display the subtree */

    AcpiDbSetOutputDestination (ACPI_DB_REDIRECTABLE_OUTPUT);
    AcpiNsDumpObjects (ACPI_TYPE_ANY, ACPI_DISPLAY_SUMMARY, MaxDepth,
        OwnerId, SubtreeEntry);
    AcpiDbSetOutputDestination (ACPI_DB_CONSOLE_OUTPUT);
}