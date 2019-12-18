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
typedef  char ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_CAST_PTR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ACPI_HANDLE ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 char* AcpiDbConvertToNode (char*) ; 
 char* AcpiFormatException (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,char*,char*) ; 
 int /*<<< orphan*/  AcpiUnloadParentTable (int /*<<< orphan*/ ) ; 

void
AcpiDbUnloadAcpiTable (
    char                    *ObjectName)
{
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_STATUS             Status;


    /* Translate name to an Named object */

    Node = AcpiDbConvertToNode (ObjectName);
    if (!Node)
    {
        return;
    }

    Status = AcpiUnloadParentTable (ACPI_CAST_PTR (ACPI_HANDLE, Node));
    if (ACPI_SUCCESS (Status))
    {
        AcpiOsPrintf ("Parent of [%s] (%p) unloaded and uninstalled\n",
            ObjectName, Node);
    }
    else
    {
        AcpiOsPrintf ("%s, while unloading parent table of [%s]\n",
            AcpiFormatException (Status), ObjectName);
    }
}