#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int AmlOpcode; scalar_t__ DisasmOpcode; char* OperatorSymbol; TYPE_4__* Next; int /*<<< orphan*/  DisasmFlags; TYPE_2__* Parent; } ;
struct TYPE_18__ {TYPE_3__ Common; } ;
struct TYPE_15__ {int /*<<< orphan*/  AmlOpcode; } ;
struct TYPE_16__ {TYPE_1__ Common; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_4__ ACPI_PARSE_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_OP_WALK_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_DASM_LNOT_PREFIX ; 
 scalar_t__ ACPI_DASM_LNOT_SUFFIX ; 
 int /*<<< orphan*/  ACPI_PARSEOP_ASSIGNMENT ; 
 int /*<<< orphan*/  ACPI_PARSEOP_CLOSING_PAREN ; 
 int /*<<< orphan*/  ACPI_PARSEOP_COMPOUND_ASSIGNMENT ; 
 int /*<<< orphan*/  ACPI_PARSEOP_IGNORE ; 
 int /*<<< orphan*/  ACPI_PARSEOP_LEGACY_ASL_ONLY ; 
#define  AML_ADD_OP 148 
#define  AML_BIT_AND_OP 147 
#define  AML_BIT_NOT_OP 146 
#define  AML_BIT_OR_OP 145 
#define  AML_BIT_XOR_OP 144 
 int AML_BUFFER_OP ; 
#define  AML_DECREMENT_OP 143 
#define  AML_DIVIDE_OP 142 
#define  AML_INCREMENT_OP 141 
#define  AML_INDEX_OP 140 
#define  AML_LOGICAL_AND_OP 139 
#define  AML_LOGICAL_EQUAL_OP 138 
#define  AML_LOGICAL_GREATER_OP 137 
#define  AML_LOGICAL_LESS_OP 136 
#define  AML_LOGICAL_NOT_OP 135 
#define  AML_LOGICAL_OR_OP 134 
#define  AML_MOD_OP 133 
#define  AML_MULTIPLY_OP 132 
 int AML_PACKAGE_OP ; 
#define  AML_SHIFT_LEFT_OP 131 
#define  AML_SHIFT_RIGHT_OP 130 
#define  AML_STORE_OP 129 
 int AML_STRING_OP ; 
#define  AML_SUBTRACT_OP 128 
 int AML_VARIABLE_PACKAGE_OP ; 
 void* AcpiDmGetCompoundSymbol (int) ; 
 int /*<<< orphan*/  AcpiDmIsOptimizationIgnored (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  AcpiDmIsTargetAnOperand (TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmIsValidTarget (TYPE_4__*) ; 
 int /*<<< orphan*/  AcpiDmPromoteTarget (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  AcpiGbl_CstyleDisassembly ; 
 int /*<<< orphan*/  AcpiGbl_DoDisassemblerOptimizations ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*) ; 
 TYPE_4__* AcpiPsGetArg (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
AcpiDmCheckForSymbolicOpcode (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_OP_WALK_INFO       *Info)
{
    char                    *OperatorSymbol = NULL;
    ACPI_PARSE_OBJECT       *Argument1;
    ACPI_PARSE_OBJECT       *Argument2;
    ACPI_PARSE_OBJECT       *Target;
    ACPI_PARSE_OBJECT       *Target2;


    /* Exit immediately if ASL+ not enabled */

    if (!AcpiGbl_CstyleDisassembly)
    {
        return (FALSE);
    }

    /* Get the first operand */

    Argument1 = AcpiPsGetArg (Op, 0);
    if (!Argument1)
    {
        return (FALSE);
    }

    /* Get the second operand */

    Argument2 = Argument1->Common.Next;

    /* Setup the operator string for this opcode */

    switch (Op->Common.AmlOpcode)
    {
    case AML_ADD_OP:
        OperatorSymbol = " + ";
        break;

    case AML_SUBTRACT_OP:
        OperatorSymbol = " - ";
        break;

    case AML_MULTIPLY_OP:
        OperatorSymbol = " * ";
        break;

    case AML_DIVIDE_OP:
        OperatorSymbol = " / ";
        break;

    case AML_MOD_OP:
        OperatorSymbol = " % ";
        break;

    case AML_SHIFT_LEFT_OP:
        OperatorSymbol = " << ";
        break;

    case AML_SHIFT_RIGHT_OP:
        OperatorSymbol = " >> ";
        break;

    case AML_BIT_AND_OP:
        OperatorSymbol = " & ";
        break;

    case AML_BIT_OR_OP:
        OperatorSymbol = " | ";
        break;

    case AML_BIT_XOR_OP:
        OperatorSymbol = " ^ ";
        break;

    /* Logical operators, no target */

    case AML_LOGICAL_AND_OP:
        OperatorSymbol = " && ";
        break;

    case AML_LOGICAL_EQUAL_OP:
        OperatorSymbol = " == ";
        break;

    case AML_LOGICAL_GREATER_OP:
        OperatorSymbol = " > ";
        break;

    case AML_LOGICAL_LESS_OP:
        OperatorSymbol = " < ";
        break;

    case AML_LOGICAL_OR_OP:
        OperatorSymbol = " || ";
        break;

    case AML_LOGICAL_NOT_OP:
        /*
         * Check for the LNOT sub-opcodes. These correspond to
         * LNotEqual, LLessEqual, and LGreaterEqual. There are
         * no actual AML opcodes for these operators.
         */
        switch (Argument1->Common.AmlOpcode)
        {
        case AML_LOGICAL_EQUAL_OP:
            OperatorSymbol = " != ";
            break;

        case AML_LOGICAL_GREATER_OP:
            OperatorSymbol = " <= ";
            break;

        case AML_LOGICAL_LESS_OP:
            OperatorSymbol = " >= ";
            break;

        default:

            /* Unary LNOT case, emit "!" immediately */

            AcpiOsPrintf ("!");
            return (TRUE);
        }

        Argument1->Common.DisasmOpcode = ACPI_DASM_LNOT_SUFFIX;
        Op->Common.DisasmOpcode = ACPI_DASM_LNOT_PREFIX;

        /* Save symbol string in the next child (not peer) */

        Argument2 = AcpiPsGetArg (Argument1, 0);
        if (!Argument2)
        {
            return (FALSE);
        }

        Argument2->Common.OperatorSymbol = OperatorSymbol;
        return (TRUE);

    case AML_INDEX_OP:
        /*
         * Check for constant source operand. Note: although technically
         * legal syntax, the iASL compiler does not support this with
         * the symbolic operators for Index(). It doesn't make sense to
         * use Index() with a constant anyway.
         */
        if ((Argument1->Common.AmlOpcode == AML_STRING_OP)  ||
            (Argument1->Common.AmlOpcode == AML_BUFFER_OP)  ||
            (Argument1->Common.AmlOpcode == AML_PACKAGE_OP) ||
            (Argument1->Common.AmlOpcode == AML_VARIABLE_PACKAGE_OP))
        {
            Op->Common.DisasmFlags |= ACPI_PARSEOP_CLOSING_PAREN;
            return (FALSE);
        }

        /* Index operator is [] */

        Argument1->Common.OperatorSymbol = " [";
        Argument2->Common.OperatorSymbol = "]";
        break;

    /* Unary operators */

    case AML_DECREMENT_OP:
        OperatorSymbol = "--";
        break;

    case AML_INCREMENT_OP:
        OperatorSymbol = "++";
        break;

    case AML_BIT_NOT_OP:
    case AML_STORE_OP:
        OperatorSymbol = NULL;
        break;

    default:
        return (FALSE);
    }

    if (Argument1->Common.DisasmOpcode == ACPI_DASM_LNOT_SUFFIX)
    {
        return (TRUE);
    }

    /*
     * This is the key to how the disassembly of the C-style operators
     * works. We save the operator symbol in the first child, thus
     * deferring symbol output until after the first operand has been
     * emitted.
     */
    if (!Argument1->Common.OperatorSymbol)
    {
        Argument1->Common.OperatorSymbol = OperatorSymbol;
    }

    /*
     * Check for a valid target as the 3rd (or sometimes 2nd) operand
     *
     * Compound assignment operator support:
     * Attempt to optimize constructs of the form:
     *      Add (Local1, 0xFF, Local1)
     * to:
     *      Local1 += 0xFF
     *
     * Only the math operators and Store() have a target.
     * Logicals have no target.
     */
    switch (Op->Common.AmlOpcode)
    {
    case AML_ADD_OP:
    case AML_SUBTRACT_OP:
    case AML_MULTIPLY_OP:
    case AML_DIVIDE_OP:
    case AML_MOD_OP:
    case AML_SHIFT_LEFT_OP:
    case AML_SHIFT_RIGHT_OP:
    case AML_BIT_AND_OP:
    case AML_BIT_OR_OP:
    case AML_BIT_XOR_OP:

        /* Target is 3rd operand */

        Target = Argument2->Common.Next;
        if (Op->Common.AmlOpcode == AML_DIVIDE_OP)
        {
            Target2 = Target->Common.Next;

            /*
             * Divide has an extra target operand (Remainder).
             * Default behavior is to simply ignore ASL+ conversion
             * if the remainder target (modulo) is specified.
             */
            if (!AcpiGbl_DoDisassemblerOptimizations)
            {
                if (AcpiDmIsValidTarget (Target))
                {
                    Argument1->Common.OperatorSymbol = NULL;
                    Op->Common.DisasmFlags |= ACPI_PARSEOP_LEGACY_ASL_ONLY;
                    return (FALSE);
                }

                Target->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;
                Target = Target2;
            }
            else
            {
                /*
                 * Divide has an extra target operand (Remainder).
                 * If both targets are specified, it cannot be converted
                 * to a C-style operator.
                 */
                if (AcpiDmIsValidTarget (Target) &&
                    AcpiDmIsValidTarget (Target2))
                {
                    Argument1->Common.OperatorSymbol = NULL;
                    Op->Common.DisasmFlags |= ACPI_PARSEOP_LEGACY_ASL_ONLY;
                    return (FALSE);
                }

                if (AcpiDmIsValidTarget (Target)) /* Only first Target is valid (remainder) */
                {
                    /* Convert the Divide to Modulo */

                    Op->Common.AmlOpcode = AML_MOD_OP;

                    Argument1->Common.OperatorSymbol = " % ";
                    Target2->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;
                }
                else /* Only second Target (quotient) is valid */
                {
                    Target->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;
                    Target = Target2;
                }
            }
        }

        /* Parser should ensure there is at least a placeholder target */

        if (!Target)
        {
            return (FALSE);
        }

        if (!AcpiDmIsValidTarget (Target))
        {
            /* Not a valid target (placeholder only, from parser) */
            break;
        }

        /*
         * Promote the target up to the first child in the parse
         * tree. This is done because the target will be output
         * first, in the form:
         *     <Target> = Operands...
         */
        AcpiDmPromoteTarget (Op, Target);

        /* Check operands for conversion to a "Compound Assignment" */

        switch (Op->Common.AmlOpcode)
        {
            /* Commutative operators */

        case AML_ADD_OP:
        case AML_MULTIPLY_OP:
        case AML_BIT_AND_OP:
        case AML_BIT_OR_OP:
        case AML_BIT_XOR_OP:
            /*
             * For the commutative operators, we can convert to a
             * compound statement only if at least one (either) operand
             * is the same as the target.
             *
             *      Add (A, B, A) --> A += B
             *      Add (B, A, A) --> A += B
             *      Add (B, C, A) --> A = (B + C)
             */
            if ((AcpiDmIsTargetAnOperand (Target, Argument1, TRUE)) ||
                (AcpiDmIsTargetAnOperand (Target, Argument2, TRUE)))
            {
                Target->Common.OperatorSymbol =
                    AcpiDmGetCompoundSymbol (Op->Common.AmlOpcode);

                /* Convert operator to compound assignment */

                Op->Common.DisasmFlags |= ACPI_PARSEOP_COMPOUND_ASSIGNMENT;
                Argument1->Common.OperatorSymbol = NULL;
                return (TRUE);
            }
            break;

            /* Non-commutative operators */

        case AML_SUBTRACT_OP:
        case AML_DIVIDE_OP:
        case AML_MOD_OP:
        case AML_SHIFT_LEFT_OP:
        case AML_SHIFT_RIGHT_OP:
            /*
             * For the non-commutative operators, we can convert to a
             * compound statement only if the target is the same as the
             * first operand.
             *
             *      Subtract (A, B, A) --> A -= B
             *      Subtract (B, A, A) --> A = (B - A)
             */
            if ((AcpiDmIsTargetAnOperand (Target, Argument1, TRUE)))
            {
                Target->Common.OperatorSymbol =
                    AcpiDmGetCompoundSymbol (Op->Common.AmlOpcode);

                /* Convert operator to compound assignment */

                Op->Common.DisasmFlags |= ACPI_PARSEOP_COMPOUND_ASSIGNMENT;
                Argument1->Common.OperatorSymbol = NULL;
                return (TRUE);
            }
            break;

        default:
            break;
        }

        /*
         * If we are within a C-style expression, emit an extra open
         * paren. Implemented by examining the parent op.
         */
        switch (Op->Common.Parent->Common.AmlOpcode)
        {
        case AML_ADD_OP:
        case AML_SUBTRACT_OP:
        case AML_MULTIPLY_OP:
        case AML_DIVIDE_OP:
        case AML_MOD_OP:
        case AML_SHIFT_LEFT_OP:
        case AML_SHIFT_RIGHT_OP:
        case AML_BIT_AND_OP:
        case AML_BIT_OR_OP:
        case AML_BIT_XOR_OP:
        case AML_LOGICAL_AND_OP:
        case AML_LOGICAL_EQUAL_OP:
        case AML_LOGICAL_GREATER_OP:
        case AML_LOGICAL_LESS_OP:
        case AML_LOGICAL_OR_OP:

            Op->Common.DisasmFlags |= ACPI_PARSEOP_ASSIGNMENT;
            AcpiOsPrintf ("(");
            break;

        default:
            break;
        }

        /* Normal output for ASL/AML operators with a target operand */

        Target->Common.OperatorSymbol = " = (";
        return (TRUE);

    /* Binary operators, no parens */

    case AML_DECREMENT_OP:
    case AML_INCREMENT_OP:
        return (TRUE);

    case AML_INDEX_OP:

        /* Target is optional, 3rd operand */

        Target = Argument2->Common.Next;
        if (AcpiDmIsValidTarget (Target))
        {
            AcpiDmPromoteTarget (Op, Target);

            if (!Target->Common.OperatorSymbol)
            {
                Target->Common.OperatorSymbol = " = ";
            }
        }
        return (TRUE);

    case AML_STORE_OP:
        /*
         * For Store, the Target is the 2nd operand. We know the target
         * is valid, because it is not optional.
         *
         * Ignore any optimizations/folding if flag is set.
         * Used for iASL/disassembler test suite only.
         */
        if (AcpiDmIsOptimizationIgnored (Op, Argument1))
        {
            return (FALSE);
        }

        /*
         * Perform conversion.
         * In the parse tree, simply swap the target with the
         * source so that the target is processed first.
         */
        Target = Argument1->Common.Next;
        if (!Target)
        {
            return (FALSE);
        }

        AcpiDmPromoteTarget (Op, Target);
        if (!Target->Common.OperatorSymbol)
        {
            Target->Common.OperatorSymbol = " = ";
        }
        return (TRUE);

    case AML_BIT_NOT_OP:

        /* Target is optional, 2nd operand */

        Target = Argument1->Common.Next;
        if (!Target)
        {
            return (FALSE);
        }

        if (AcpiDmIsValidTarget (Target))
        {
            /* Valid target, not a placeholder */

            AcpiDmPromoteTarget (Op, Target);
            Target->Common.OperatorSymbol = " = ~";
        }
        else
        {
            /* No target. Emit this prefix operator immediately */

            AcpiOsPrintf ("~");
        }
        return (TRUE);

    default:
        break;
    }

    /* All other operators, emit an open paren */

    AcpiOsPrintf ("(");
    return (TRUE);
}