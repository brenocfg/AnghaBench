#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_6__* Arg; } ;
struct TYPE_13__ {scalar_t__ AmlOpcode; scalar_t__ DisasmOpcode; TYPE_6__* Next; int /*<<< orphan*/  DisasmFlags; TYPE_4__ Value; int /*<<< orphan*/  Parent; } ;
struct TYPE_11__ {TYPE_2__* Next; } ;
struct TYPE_14__ {TYPE_5__ Common; TYPE_3__ Asl; } ;
struct TYPE_9__ {scalar_t__ AmlOpcode; } ;
struct TYPE_10__ {TYPE_1__ Common; } ;
typedef  TYPE_6__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_DASM_CASE ; 
 scalar_t__ ACPI_DASM_DEFAULT ; 
 scalar_t__ ACPI_DASM_LNOT_PREFIX ; 
 int /*<<< orphan*/  ACPI_PARSEOP_ELSEIF ; 
 int /*<<< orphan*/  ACPI_PARSEOP_IGNORE ; 
 scalar_t__ AML_ELSE_OP ; 
 scalar_t__ AML_IF_OP ; 
 int /*<<< orphan*/  AcpiDmPromoteSubtree (TYPE_6__*) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,char*) ; 

__attribute__((used)) static void
AcpiDmConvertToElseIf (
    ACPI_PARSE_OBJECT       *OriginalElseOp)
{
    ACPI_PARSE_OBJECT       *IfOp;
    ACPI_PARSE_OBJECT       *ElseOp;


    /*
     * To be able to perform the conversion, two conditions must be satisfied:
     * 1) The first child of the Else must be an If statement.
     * 2) The If block can only be followed by an Else block and these must
     *    be the only blocks under the original Else.
     */
    IfOp = OriginalElseOp->Common.Value.Arg;

    if (!IfOp ||
        (IfOp->Common.AmlOpcode != AML_IF_OP) ||
        (IfOp->Asl.Next && (IfOp->Asl.Next->Common.AmlOpcode != AML_ELSE_OP)))
    {
        /* Not a proper Else..If sequence, cannot convert to ElseIf */

        if (OriginalElseOp->Common.DisasmOpcode == ACPI_DASM_DEFAULT)
        {
            AcpiOsPrintf ("%s", "Default");
            return;
        }

        AcpiOsPrintf ("%s", "Else");
        return;
    }

    /* Cannot have anything following the If...Else block */

    ElseOp = IfOp->Common.Next;
    if (ElseOp && ElseOp->Common.Next)
    {
        if (OriginalElseOp->Common.DisasmOpcode == ACPI_DASM_DEFAULT)
        {
            AcpiOsPrintf ("%s", "Default");
            return;
        }

        AcpiOsPrintf ("%s", "Else");
        return;
    }

    if (OriginalElseOp->Common.DisasmOpcode == ACPI_DASM_DEFAULT)
    {
        /*
         * There is an ElseIf but in this case the Else is actually
         * a Default block for a Switch/Case statement. No conversion.
         */
        AcpiOsPrintf ("%s", "Default");
        return;
    }

    if (OriginalElseOp->Common.DisasmOpcode == ACPI_DASM_CASE)
    {
        /*
         * This ElseIf is actually a Case block for a Switch/Case
         * statement. Print Case but do not return so that we can
         * promote the subtree and keep the indentation level.
         */
        AcpiOsPrintf ("%s", "Case");
    }
    else
    {
       /* Emit ElseIf, mark the IF as now an ELSEIF */

        AcpiOsPrintf ("%s", "ElseIf");
    }

    IfOp->Common.DisasmFlags |= ACPI_PARSEOP_ELSEIF;

    /* The IF parent will now be the same as the original ELSE parent */

    IfOp->Common.Parent = OriginalElseOp->Common.Parent;

    /*
     * Update the NEXT pointers to restructure the parse tree, essentially
     * promoting an If..Else block up to the same level as the original
     * Else.
     *
     * Check if the IF has a corresponding ELSE peer
     */
    ElseOp = IfOp->Common.Next;
    if (ElseOp &&
        (ElseOp->Common.AmlOpcode == AML_ELSE_OP))
    {
        /* If an ELSE matches the IF, promote it also */

        ElseOp->Common.Parent = OriginalElseOp->Common.Parent;

        /* Promote the entire block under the ElseIf (All Next OPs) */

        AcpiDmPromoteSubtree (OriginalElseOp);
    }
    else
    {
        /* Otherwise, set the IF NEXT to the original ELSE NEXT */

        IfOp->Common.Next = OriginalElseOp->Common.Next;
    }

    /* Detach the child IF block from the original ELSE */

    OriginalElseOp->Common.Value.Arg = NULL;

    /* Ignore the original ELSE from now on */

    OriginalElseOp->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;
    OriginalElseOp->Common.DisasmOpcode = ACPI_DASM_LNOT_PREFIX;

    /* Insert IF (now ELSEIF) as next peer of the original ELSE */

    OriginalElseOp->Common.Next = IfOp;
}