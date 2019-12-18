#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* Arg; } ;
struct TYPE_8__ {int AmlOpcode; int /*<<< orphan*/  DisasmFlags; TYPE_3__* Next; TYPE_1__ Value; } ;
struct TYPE_9__ {TYPE_2__ Common; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_PARSEOP_LEGACY_ASL_ONLY ; 
#define  AML_ADD_OP 139 
#define  AML_BIT_AND_OP 138 
#define  AML_BIT_NOT_OP 137 
#define  AML_BIT_OR_OP 136 
#define  AML_BIT_XOR_OP 135 
#define  AML_DIVIDE_OP 134 
#define  AML_INDEX_OP 133 
#define  AML_MOD_OP 132 
#define  AML_MULTIPLY_OP 131 
#define  AML_SHIFT_LEFT_OP 130 
#define  AML_SHIFT_RIGHT_OP 129 
#define  AML_SUBTRACT_OP 128 
 int /*<<< orphan*/  AcpiDmIsValidTarget (TYPE_3__*) ; 
 scalar_t__ AcpiGbl_DoDisassemblerOptimizations ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN
AcpiDmIsOptimizationIgnored (
    ACPI_PARSE_OBJECT       *StoreOp,
    ACPI_PARSE_OBJECT       *StoreArgument)
{
    ACPI_PARSE_OBJECT       *Argument1;
    ACPI_PARSE_OBJECT       *Argument2;
    ACPI_PARSE_OBJECT       *Target;


    /* No optimizations/folding for the typical case */

    if (AcpiGbl_DoDisassemblerOptimizations)
    {
        return (FALSE);
    }

    /*
     * Only a small subset of ASL/AML operators can be optimized.
     * Can only optimize/fold if there is no target (or targets)
     * specified for the operator. And of course, the operator
     * is surrrounded by a Store() operator.
     */
    switch (StoreArgument->Common.AmlOpcode)
    {
    case AML_ADD_OP:
    case AML_SUBTRACT_OP:
    case AML_MULTIPLY_OP:
    case AML_MOD_OP:
    case AML_SHIFT_LEFT_OP:
    case AML_SHIFT_RIGHT_OP:
    case AML_BIT_AND_OP:
    case AML_BIT_OR_OP:
    case AML_BIT_XOR_OP:
    case AML_INDEX_OP:

        /* These operators have two arguments and one target */

        Argument1 = StoreArgument->Common.Value.Arg;
        Argument2 = Argument1->Common.Next;
        Target = Argument2->Common.Next;

        if (!AcpiDmIsValidTarget (Target))
        {
            StoreOp->Common.DisasmFlags |= ACPI_PARSEOP_LEGACY_ASL_ONLY;
            return (TRUE);
        }
        break;

    case AML_DIVIDE_OP:

        /* This operator has two arguments and two targets */

        Argument1 = StoreArgument->Common.Value.Arg;
        Argument2 = Argument1->Common.Next;
        Target = Argument2->Common.Next;

        if (!AcpiDmIsValidTarget (Target) ||
            !AcpiDmIsValidTarget (Target->Common.Next))
        {
            StoreOp->Common.DisasmFlags |= ACPI_PARSEOP_LEGACY_ASL_ONLY;
            return (TRUE);
        }
        break;

    case AML_BIT_NOT_OP:

        /* This operator has one operand and one target */

        Argument1 = StoreArgument->Common.Value.Arg;
        Target = Argument1->Common.Next;

        if (!AcpiDmIsValidTarget (Target))
        {
            StoreOp->Common.DisasmFlags |= ACPI_PARSEOP_LEGACY_ASL_ONLY;
            return (TRUE);
        }
        break;

    default:
        break;
    }

    return (FALSE);
}