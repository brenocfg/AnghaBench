#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ Pointer; int /*<<< orphan*/  Length; } ;
struct TYPE_14__ {int /*<<< orphan*/  Type; } ;
struct TYPE_11__ {int /*<<< orphan*/  Handle; int /*<<< orphan*/  ActualType; } ;
struct TYPE_13__ {int Type; TYPE_1__ Reference; } ;
struct TYPE_12__ {int Count; TYPE_3__* Pointer; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int ACPI_OBJECT_TYPE ;
typedef  TYPE_2__ ACPI_OBJECT_LIST ;
typedef  TYPE_3__ ACPI_OBJECT ;
typedef  TYPE_4__ ACPI_NAMESPACE_NODE ;
typedef  TYPE_5__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 int /*<<< orphan*/  ACPI_CAST_PTR (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE ; 
#define  ACPI_TYPE_BUFFER 131 
#define  ACPI_TYPE_INTEGER 130 
 int ACPI_TYPE_LOCAL_REFERENCE ; 
#define  ACPI_TYPE_PACKAGE 129 
#define  ACPI_TYPE_STRING 128 
 int /*<<< orphan*/  AE_TYPE ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiFormatException (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGbl_MethodExecuting ; 
 int /*<<< orphan*/  AcpiOsFree (scalar_t__) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  AcpiUtGetTypeName (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ReadHandle ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static ACPI_STATUS
AcpiDbReadFromObject (
    ACPI_NAMESPACE_NODE     *Node,
    ACPI_OBJECT_TYPE        ExpectedType,
    ACPI_OBJECT             **Value)
{
    ACPI_OBJECT             *RetValue;
    ACPI_OBJECT_LIST        ParamObjects;
    ACPI_OBJECT             Params[2];
    ACPI_BUFFER             ReturnObj;
    ACPI_STATUS             Status;


    Params[0].Type = ACPI_TYPE_LOCAL_REFERENCE;
    Params[0].Reference.ActualType = Node->Type;
    Params[0].Reference.Handle = ACPI_CAST_PTR (ACPI_HANDLE, Node);

    ParamObjects.Count = 1;
    ParamObjects.Pointer = Params;

    ReturnObj.Length  = ACPI_ALLOCATE_BUFFER;

    AcpiGbl_MethodExecuting = TRUE;
    Status = AcpiEvaluateObject (ReadHandle, NULL,
        &ParamObjects, &ReturnObj);

    AcpiGbl_MethodExecuting = FALSE;
    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("Could not read from object, %s",
            AcpiFormatException (Status));
        return (Status);
    }

    RetValue = (ACPI_OBJECT *) ReturnObj.Pointer;

    switch (RetValue->Type)
    {
    case ACPI_TYPE_INTEGER:
    case ACPI_TYPE_BUFFER:
    case ACPI_TYPE_STRING:
    case ACPI_TYPE_PACKAGE:
        /*
         * Did we receive the type we wanted? Most important for the
         * Integer/Buffer case (when a field is larger than an Integer,
         * it should return a Buffer).
         */
        if (RetValue->Type != ExpectedType)
        {
            AcpiOsPrintf (" Type mismatch:  Expected %s, Received %s",
                AcpiUtGetTypeName (ExpectedType),
                AcpiUtGetTypeName (RetValue->Type));

            AcpiOsFree (ReturnObj.Pointer);
            return (AE_TYPE);
        }

        *Value = RetValue;
        break;

    default:

        AcpiOsPrintf (" Unsupported return object type, %s",
            AcpiUtGetTypeName (RetValue->Type));

        AcpiOsFree (ReturnObj.Pointer);
        return (AE_TYPE);
    }

    return (Status);
}