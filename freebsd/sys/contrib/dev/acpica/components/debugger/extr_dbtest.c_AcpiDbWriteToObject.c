#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  Type; } ;
struct TYPE_11__ {int /*<<< orphan*/  Handle; int /*<<< orphan*/  ActualType; } ;
struct TYPE_13__ {TYPE_1__ Reference; int /*<<< orphan*/  Type; } ;
struct TYPE_12__ {int Count; TYPE_3__* Pointer; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OBJECT_LIST ;
typedef  TYPE_3__ ACPI_OBJECT ;
typedef  TYPE_4__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_CAST_PTR (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_REFERENCE ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiFormatException (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGbl_MethodExecuting ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WriteHandle ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 

__attribute__((used)) static ACPI_STATUS
AcpiDbWriteToObject (
    ACPI_NAMESPACE_NODE     *Node,
    ACPI_OBJECT             *Value)
{
    ACPI_OBJECT_LIST        ParamObjects;
    ACPI_OBJECT             Params[2];
    ACPI_STATUS             Status;


    Params[0].Type = ACPI_TYPE_LOCAL_REFERENCE;
    Params[0].Reference.ActualType = Node->Type;
    Params[0].Reference.Handle = ACPI_CAST_PTR (ACPI_HANDLE, Node);

    /* Copy the incoming user parameter */

    memcpy (&Params[1], Value, sizeof (ACPI_OBJECT));

    ParamObjects.Count = 2;
    ParamObjects.Pointer = Params;

    AcpiGbl_MethodExecuting = TRUE;
    Status = AcpiEvaluateObject (WriteHandle, NULL, &ParamObjects, NULL);
    AcpiGbl_MethodExecuting = FALSE;

    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("Could not write to object, %s",
            AcpiFormatException (Status));
    }

    return (Status);
}