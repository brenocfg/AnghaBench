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
typedef  int /*<<< orphan*/  ACPI_SIZE ;
typedef  char ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 scalar_t__ ACPI_DESC_TYPE_NAMED ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (char*) ; 
 char* ACPI_TO_POINTER (int /*<<< orphan*/ ) ; 
 char* AcpiDbLocalNsLookup (char*) ; 
 char* AcpiGbl_RootNode ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,char*,...) ; 
 int /*<<< orphan*/  AcpiOsReadable (char*,int) ; 
 int /*<<< orphan*/  AcpiUtGetDescriptorName (char*) ; 
 int /*<<< orphan*/  strtoul (char*,int /*<<< orphan*/ *,int) ; 

ACPI_NAMESPACE_NODE *
AcpiDbConvertToNode (
    char                    *InString)
{
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_SIZE               Address;


    if ((*InString >= 0x30) && (*InString <= 0x39))
    {
        /* Numeric argument, convert */

        Address = strtoul (InString, NULL, 16);
        Node = ACPI_TO_POINTER (Address);
        if (!AcpiOsReadable (Node, sizeof (ACPI_NAMESPACE_NODE)))
        {
            AcpiOsPrintf ("Address %p is invalid", Node);
            return (NULL);
        }

        /* Make sure pointer is valid NS node */

        if (ACPI_GET_DESCRIPTOR_TYPE (Node) != ACPI_DESC_TYPE_NAMED)
        {
            AcpiOsPrintf ("Address %p is not a valid namespace node [%s]\n",
                Node, AcpiUtGetDescriptorName (Node));
            return (NULL);
        }
    }
    else
    {
        /*
         * Alpha argument: The parameter is a name string that must be
         * resolved to a Namespace object.
         */
        Node = AcpiDbLocalNsLookup (InString);
        if (!Node)
        {
            AcpiOsPrintf (
                "Could not find [%s] in namespace, defaulting to root node\n",
                InString);
            Node = AcpiGbl_RootNode;
        }
    }

    return (Node);
}