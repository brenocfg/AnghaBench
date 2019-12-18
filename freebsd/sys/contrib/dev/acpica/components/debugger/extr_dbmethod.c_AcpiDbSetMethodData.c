#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT64 ;
typedef  size_t UINT32 ;
struct TYPE_20__ {scalar_t__ Type; TYPE_5__* Object; } ;
struct TYPE_15__ {size_t Value; } ;
struct TYPE_19__ {TYPE_1__ Integer; } ;
struct TYPE_18__ {TYPE_3__* LocalVariables; TYPE_2__* Arguments; } ;
struct TYPE_17__ {TYPE_5__* Object; } ;
struct TYPE_16__ {TYPE_5__* Object; } ;
typedef  TYPE_4__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_5__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_6__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 size_t ACPI_METHOD_MAX_ARG ; 
 size_t ACPI_METHOD_MAX_LOCAL ; 
 int /*<<< orphan*/  ACPI_REFCLASS_ARG ; 
 int /*<<< orphan*/  ACPI_REFCLASS_LOCAL ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 TYPE_6__* AcpiDbConvertToNode (char*) ; 
 int /*<<< orphan*/  AcpiDbDisplayInternalObject (TYPE_5__*,TYPE_4__*) ; 
 TYPE_4__* AcpiDsGetCurrentWalkState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDsStoreObjectToLocal (int /*<<< orphan*/ ,size_t,TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  AcpiGbl_CurrentWalkList ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 TYPE_5__* AcpiUtCreateIntegerObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiUtStrupr (char*) ; 
 size_t strtoul (char*,int /*<<< orphan*/ *,int) ; 

void
AcpiDbSetMethodData (
    char                    *TypeArg,
    char                    *IndexArg,
    char                    *ValueArg)
{
    char                    Type;
    UINT32                  Index;
    UINT32                  Value;
    ACPI_WALK_STATE         *WalkState;
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_STATUS             Status;
    ACPI_NAMESPACE_NODE     *Node;


    /* Validate TypeArg */

    AcpiUtStrupr (TypeArg);
    Type = TypeArg[0];
    if ((Type != 'L') &&
        (Type != 'A') &&
        (Type != 'N'))
    {
        AcpiOsPrintf ("Invalid SET operand: %s\n", TypeArg);
        return;
    }

    Value = strtoul (ValueArg, NULL, 16);

    if (Type == 'N')
    {
        Node = AcpiDbConvertToNode (IndexArg);
        if (!Node)
        {
            return;
        }

        if (Node->Type != ACPI_TYPE_INTEGER)
        {
            AcpiOsPrintf ("Can only set Integer nodes\n");
            return;
        }
        ObjDesc = Node->Object;
        ObjDesc->Integer.Value = Value;
        return;
    }

    /* Get the index and value */

    Index = strtoul (IndexArg, NULL, 16);

    WalkState = AcpiDsGetCurrentWalkState (AcpiGbl_CurrentWalkList);
    if (!WalkState)
    {
        AcpiOsPrintf ("There is no method currently executing\n");
        return;
    }

    /* Create and initialize the new object */

    ObjDesc = AcpiUtCreateIntegerObject ((UINT64) Value);
    if (!ObjDesc)
    {
        AcpiOsPrintf ("Could not create an internal object\n");
        return;
    }

    /* Store the new object into the target */

    switch (Type)
    {
    case 'A':

        /* Set a method argument */

        if (Index > ACPI_METHOD_MAX_ARG)
        {
            AcpiOsPrintf ("Arg%u - Invalid argument name\n",
                Index);
            goto Cleanup;
        }

        Status = AcpiDsStoreObjectToLocal (ACPI_REFCLASS_ARG,
            Index, ObjDesc, WalkState);
        if (ACPI_FAILURE (Status))
        {
            goto Cleanup;
        }

        ObjDesc = WalkState->Arguments[Index].Object;

        AcpiOsPrintf ("Arg%u: ", Index);
        AcpiDbDisplayInternalObject (ObjDesc, WalkState);
        break;

    case 'L':

        /* Set a method local */

        if (Index > ACPI_METHOD_MAX_LOCAL)
        {
            AcpiOsPrintf ("Local%u - Invalid local variable name\n",
                Index);
            goto Cleanup;
        }

        Status = AcpiDsStoreObjectToLocal (ACPI_REFCLASS_LOCAL,
            Index, ObjDesc, WalkState);
        if (ACPI_FAILURE (Status))
        {
            goto Cleanup;
        }

        ObjDesc = WalkState->LocalVariables[Index].Object;

        AcpiOsPrintf ("Local%u: ", Index);
        AcpiDbDisplayInternalObject (ObjDesc, WalkState);
        break;

    default:

        break;
    }

Cleanup:
    AcpiUtRemoveReference (ObjDesc);
}