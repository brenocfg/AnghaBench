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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int UINT16 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int ACPI_EXT_INTERNAL_PATH_ALLOCATED ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmCreateNewExternal (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AcpiDmGetExternalAndInternalPath (int /*<<< orphan*/ *,char**,char**) ; 
 int /*<<< orphan*/  AcpiDmRemoveRootPrefix (char**) ; 
 int /*<<< orphan*/  DmAddNodeToExternalList ; 
 int /*<<< orphan*/  return_VOID ; 

void
AcpiDmAddNodeToExternalList (
    ACPI_NAMESPACE_NODE     *Node,
    UINT8                   Type,
    UINT32                  Value,
    UINT16                  Flags)
{
    char                    *ExternalPath;
    char                    *InternalPath;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (DmAddNodeToExternalList);

    /* Get the full external and internal pathnames to the node */

    Status = AcpiDmGetExternalAndInternalPath (Node, &ExternalPath, &InternalPath);
    if (ACPI_FAILURE (Status))
    {
        return_VOID;
    }

    /* Remove the root backslash */

    Status = AcpiDmRemoveRootPrefix (&ExternalPath);
    if (ACPI_FAILURE (Status))
    {
        ACPI_FREE (ExternalPath);
        ACPI_FREE (InternalPath);
        return_VOID;
    }

    /* Create the new External() declaration node */

    Status = AcpiDmCreateNewExternal (ExternalPath, InternalPath, Type,
        Value, (Flags | ACPI_EXT_INTERNAL_PATH_ALLOCATED));
    if (ACPI_FAILURE (Status))
    {
        ACPI_FREE (ExternalPath);
        ACPI_FREE (InternalPath);
    }

    return_VOID;
}