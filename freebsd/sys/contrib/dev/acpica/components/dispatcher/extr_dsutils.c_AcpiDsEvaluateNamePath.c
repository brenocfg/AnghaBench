#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT8 ;
struct TYPE_23__ {scalar_t__ Type; } ;
struct TYPE_27__ {TYPE_3__ Common; } ;
struct TYPE_24__ {int Flags; TYPE_2__* Parent; } ;
struct TYPE_26__ {TYPE_4__ Common; } ;
struct TYPE_25__ {TYPE_7__* ResultObj; TYPE_7__** Operands; TYPE_6__* Op; } ;
struct TYPE_21__ {scalar_t__ AmlOpcode; } ;
struct TYPE_22__ {TYPE_1__ Common; } ;
typedef  TYPE_5__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_6__ ACPI_PARSE_OBJECT ;
typedef  TYPE_7__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int ACPI_PARSEOP_IN_STACK ; 
 int ACPI_PARSEOP_TARGET ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ AML_PACKAGE_OP ; 
 scalar_t__ AML_REF_OF_OP ; 
 scalar_t__ AML_VARIABLE_PACKAGE_OP ; 
 int /*<<< orphan*/  AcpiDsCreateOperand (TYPE_5__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDsObjStackPop (int,TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiDsResultPush (TYPE_7__*,TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiExResolveToValue (TYPE_7__**,TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiUtCopyIobjectToIobject (TYPE_7__*,TYPE_7__**,TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_7__*) ; 
 int /*<<< orphan*/  DsEvaluateNamePath ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiDsEvaluateNamePath (
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_PARSE_OBJECT       *Op = WalkState->Op;
    ACPI_OPERAND_OBJECT     **Operand = &WalkState->Operands[0];
    ACPI_OPERAND_OBJECT     *NewObjDesc;
    UINT8                   Type;


    ACPI_FUNCTION_TRACE_PTR (DsEvaluateNamePath, WalkState);


    if (!Op->Common.Parent)
    {
        /* This happens after certain exception processing */

        goto Exit;
    }

    if ((Op->Common.Parent->Common.AmlOpcode == AML_PACKAGE_OP) ||
        (Op->Common.Parent->Common.AmlOpcode == AML_VARIABLE_PACKAGE_OP) ||
        (Op->Common.Parent->Common.AmlOpcode == AML_REF_OF_OP))
    {
        /* TBD: Should we specify this feature as a bit of OpInfo->Flags of these opcodes? */

        goto Exit;
    }

    Status = AcpiDsCreateOperand (WalkState, Op, 0);
    if (ACPI_FAILURE (Status))
    {
        goto Exit;
    }

    if (Op->Common.Flags & ACPI_PARSEOP_TARGET)
    {
        NewObjDesc = *Operand;
        goto PushResult;
    }

    Type = (*Operand)->Common.Type;

    Status = AcpiExResolveToValue (Operand, WalkState);
    if (ACPI_FAILURE (Status))
    {
        goto Exit;
    }

    if (Type == ACPI_TYPE_INTEGER)
    {
        /* It was incremented by AcpiExResolveToValue */

        AcpiUtRemoveReference (*Operand);

        Status = AcpiUtCopyIobjectToIobject (
            *Operand, &NewObjDesc, WalkState);
        if (ACPI_FAILURE (Status))
        {
            goto Exit;
        }
    }
    else
    {
        /*
         * The object either was anew created or is
         * a Namespace node - don't decrement it.
         */
        NewObjDesc = *Operand;
    }

    /* Cleanup for name-path operand */

    Status = AcpiDsObjStackPop (1, WalkState);
    if (ACPI_FAILURE (Status))
    {
        WalkState->ResultObj = NewObjDesc;
        goto Exit;
    }

PushResult:

    WalkState->ResultObj = NewObjDesc;

    Status = AcpiDsResultPush (WalkState->ResultObj, WalkState);
    if (ACPI_SUCCESS (Status))
    {
        /* Force to take it from stack */

        Op->Common.Flags |= ACPI_PARSEOP_IN_STACK;
    }

Exit:

    return_ACPI_STATUS (Status);
}