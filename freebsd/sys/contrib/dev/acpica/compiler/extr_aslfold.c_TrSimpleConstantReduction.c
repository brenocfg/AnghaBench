#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/ * Child; } ;
struct TYPE_13__ {TYPE_4__* Parent; int /*<<< orphan*/  AmlOpcode; } ;
struct TYPE_16__ {TYPE_2__ Asl; TYPE_1__ Common; } ;
struct TYPE_15__ {int /*<<< orphan*/ ** CallerReturnDesc; } ;
typedef  TYPE_3__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_4__ ACPI_PARSE_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AML_INT_EVAL_SUBTREE_OP ; 
 int /*<<< orphan*/  ASL_PARSE_OUTPUT ; 
 int /*<<< orphan*/  ASL_WALK_VISIT_TWICE ; 
 int /*<<< orphan*/  AcpiDsResultPop (int /*<<< orphan*/ **,TYPE_3__*) ; 
 int /*<<< orphan*/  AcpiFormatException (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  OpcAmlEvaluationWalk1 ; 
 int /*<<< orphan*/  OpcAmlEvaluationWalk2 ; 
 int /*<<< orphan*/  PARSEOP_INTEGER ; 
 TYPE_4__* TrAllocateOp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TrInstallReducedConstant (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TrWalkParseTree (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  UtSetParseOpName (TYPE_4__*) ; 

__attribute__((used)) static ACPI_STATUS
TrSimpleConstantReduction (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_PARSE_OBJECT       *RootOp;
    ACPI_PARSE_OBJECT       *OriginalParentOp;
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_STATUS             Status;


    DbgPrint (ASL_PARSE_OUTPUT,
        "Simple subtree constant reduction, operator to constant\n");

    /* Allocate a new temporary root for this subtree */

    RootOp = TrAllocateOp (PARSEOP_INTEGER);
    if (!RootOp)
    {
        return (AE_NO_MEMORY);
    }

    RootOp->Common.AmlOpcode = AML_INT_EVAL_SUBTREE_OP;

    OriginalParentOp = Op->Common.Parent;
    Op->Common.Parent = RootOp;

    /* Hand off the subtree to the AML interpreter */

    WalkState->CallerReturnDesc = &ObjDesc;

    Status = TrWalkParseTree (Op, ASL_WALK_VISIT_TWICE,
        OpcAmlEvaluationWalk1, OpcAmlEvaluationWalk2, WalkState);

    /* Restore original parse tree */

    Op->Common.Parent = OriginalParentOp;

    if (ACPI_FAILURE (Status))
    {
        DbgPrint (ASL_PARSE_OUTPUT,
            "Constant Subtree evaluation(1), %s\n",
            AcpiFormatException (Status));
        return (Status);
    }

    /* Get the final result */

    Status = AcpiDsResultPop (&ObjDesc, WalkState);
    if (ACPI_FAILURE (Status))
    {
        DbgPrint (ASL_PARSE_OUTPUT,
            "Constant Subtree evaluation(2), %s\n",
            AcpiFormatException (Status));
        return (Status);
    }

    /* Disconnect any existing children, install new constant */

    Op->Asl.Child = NULL;
    TrInstallReducedConstant (Op, ObjDesc);

    UtSetParseOpName (Op);
    return (AE_OK);
}