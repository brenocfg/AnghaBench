#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* InternalPath; struct TYPE_7__* Next; int /*<<< orphan*/  Flags; } ;
struct TYPE_6__ {int Flags; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_NAMESPACE_NODE ;
typedef  TYPE_2__ ACPI_EXTERNAL_LIST ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EXT_CONFLICTING_DECLARATION ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ AML_ROOT_PREFIX ; 
 int ANOBJ_IS_EXTERNAL ; 
 int /*<<< orphan*/  AcpiDmGetExternalAndInternalPath (TYPE_1__*,char**,char**) ; 
 int /*<<< orphan*/  AcpiDmRemoveRootPrefix (char**) ; 
 TYPE_2__* AcpiGbl_ExternalList ; 
 int /*<<< orphan*/  DmMarkExternalConflict ; 
 int /*<<< orphan*/  return_VOID ; 
 int /*<<< orphan*/  strcmp (scalar_t__*,char*) ; 

void
AcpiDmMarkExternalConflict (
    ACPI_NAMESPACE_NODE     *Node)
{
    ACPI_EXTERNAL_LIST      *ExternalList = AcpiGbl_ExternalList;
    char                    *ExternalPath;
    char                    *InternalPath;
    char                    *Temp;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (DmMarkExternalConflict);


    if (Node->Flags & ANOBJ_IS_EXTERNAL)
    {
        return_VOID;
    }

    /* Get the full external and internal pathnames to the node */

    Status = AcpiDmGetExternalAndInternalPath (Node,
        &ExternalPath, &InternalPath);
    if (ACPI_FAILURE (Status))
    {
        return_VOID;
    }

    /* Remove the root backslash */

    Status = AcpiDmRemoveRootPrefix (&InternalPath);
    if (ACPI_FAILURE (Status))
    {
        ACPI_FREE (InternalPath);
        ACPI_FREE (ExternalPath);
        return_VOID;
    }

    while (ExternalList)
    {
        Temp = ExternalList->InternalPath;
        if ((*ExternalList->InternalPath == AML_ROOT_PREFIX) &&
            (ExternalList->InternalPath[1]))
        {
            Temp++;
        }

        if (!strcmp (ExternalList->InternalPath, InternalPath))
        {
            ExternalList->Flags |= ACPI_EXT_CONFLICTING_DECLARATION;
        }
        ExternalList = ExternalList->Next;
    }

    ACPI_FREE (InternalPath);
    ACPI_FREE (ExternalPath);

    return_VOID;
}