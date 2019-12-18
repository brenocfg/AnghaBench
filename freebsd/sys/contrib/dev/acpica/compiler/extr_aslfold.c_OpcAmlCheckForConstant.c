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
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_14__ {int Flags; } ;
struct TYPE_11__ {scalar_t__ AmlOpcode; int CompileFlags; scalar_t__ ParseOpcode; int /*<<< orphan*/  ParseOpName; TYPE_5__* Parent; int /*<<< orphan*/  LogicalLineNumber; } ;
struct TYPE_9__ {scalar_t__ AmlOpcode; } ;
struct TYPE_13__ {TYPE_3__ Asl; TYPE_1__ Common; } ;
struct TYPE_12__ {scalar_t__ Opcode; TYPE_2__* OpInfo; TYPE_5__* Op; } ;
struct TYPE_10__ {int Flags; } ;
typedef  TYPE_4__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_5__ ACPI_PARSE_OBJECT ;
typedef  TYPE_6__ ACPI_OPCODE_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_CTRL_RETURN_VALUE ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_TYPE ; 
 scalar_t__ AML_BUFFER_OP ; 
 int AML_CONSTANT ; 
 int AML_DEFER ; 
 scalar_t__ AML_NAME_OP ; 
 scalar_t__ AML_RAW_DATA_BYTE ; 
 scalar_t__ AML_RAW_DATA_DWORD ; 
 scalar_t__ AML_RAW_DATA_QWORD ; 
 scalar_t__ AML_RAW_DATA_WORD ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_CONSTANT_REQUIRED ; 
 int /*<<< orphan*/  ASL_MSG_INVALID_TARGET ; 
 int /*<<< orphan*/  ASL_MSG_UNSUPPORTED ; 
 int /*<<< orphan*/  ASL_PARSE_OUTPUT ; 
 void* AcpiPsGetOpcodeInfo (scalar_t__) ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,char*) ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*,...) ; 
 int OP_COULD_NOT_REDUCE ; 
 int OP_IS_TARGET ; 
 int OP_IS_TERM_ARG ; 
 scalar_t__ PARSEOP_ZERO ; 
 int /*<<< orphan*/  TrPrintOpFlags (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
OpcAmlCheckForConstant (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{
    ACPI_WALK_STATE         *WalkState = Context;
    ACPI_STATUS             Status = AE_OK;
    ACPI_PARSE_OBJECT       *NextOp;
    const ACPI_OPCODE_INFO  *OpInfo;


    WalkState->Op = Op;
    WalkState->Opcode = Op->Common.AmlOpcode;
    WalkState->OpInfo = AcpiPsGetOpcodeInfo (Op->Common.AmlOpcode);

    DbgPrint (ASL_PARSE_OUTPUT, "[%.4d] Opcode: %12.12s ",
        Op->Asl.LogicalLineNumber, Op->Asl.ParseOpName);

    /*
     * These opcodes do not appear in the OpcodeInfo table, but
     * they represent constants, so abort the constant walk now.
     */
    if ((WalkState->Opcode == AML_RAW_DATA_BYTE) ||
        (WalkState->Opcode == AML_RAW_DATA_WORD) ||
        (WalkState->Opcode == AML_RAW_DATA_DWORD) ||
        (WalkState->Opcode == AML_RAW_DATA_QWORD))
    {
        DbgPrint (ASL_PARSE_OUTPUT, "RAW DATA");
        Status = AE_TYPE;
        goto CleanupAndExit;
    }

    /*
     * Search upwards for a possible Name() operator. This is done
     * because a type 3/4/5 opcode within a Name() expression
     * MUST be reduced to a simple constant.
     */
    NextOp = Op->Asl.Parent;
    while (NextOp)
    {
        /* Finished if we find a Name() opcode */

        if (NextOp->Asl.AmlOpcode == AML_NAME_OP)
        {
            break;
        }

        /*
         * Any "deferred" opcodes contain one or more TermArg parameters,
         * and thus are not required to be folded to constants at compile
         * time. This affects things like Buffer() and Package() objects.
         * We just ignore them here. However, any sub-expressions can and
         * will still be typechecked. Note: These are called the
         * "deferred" opcodes in the AML interpreter.
         */
        OpInfo = AcpiPsGetOpcodeInfo (NextOp->Common.AmlOpcode);
        if (OpInfo->Flags & AML_DEFER)
        {
            NextOp = NULL;
            break;
        }

        NextOp = NextOp->Asl.Parent;
    }

    /* Type 3/4/5 opcodes have the AML_CONSTANT flag set */

    if (!(WalkState->OpInfo->Flags & AML_CONSTANT))
    {
        /*
         * From the ACPI specification:
         *
         * "The Type 3/4/5 opcodes return a value and can be used in an
         * expression that evaluates to a constant. These opcodes may be
         * evaluated at ASL compile-time. To ensure that these opcodes
         * will evaluate to a constant, the following rules apply: The
         * term cannot have a destination (target) operand, and must have
         * either a Type3Opcode, Type4Opcode, Type5Opcode, ConstExprTerm,
         * Integer, BufferTerm, Package, or String for all arguments."
         */

        /*
         * The value (second) operand for the Name() operator MUST
         * reduce to a single constant, as per the ACPI specification
         * (the operand is a DataObject). This also implies that there
         * can be no target operand. Name() is the only ASL operator
         * with a "DataObject" as an operand and is thus special-
         * cased here.
         */
        if (NextOp) /* Inspect a Name() operator */
        {
            /* Error if there is a target operand */

            if (Op->Asl.CompileFlags & OP_IS_TARGET)
            {
                AslError (ASL_ERROR, ASL_MSG_INVALID_TARGET, Op, NULL);
                Status = AE_TYPE;
            }

            /* Error if expression cannot be reduced (folded) */

            if (!(NextOp->Asl.CompileFlags & OP_COULD_NOT_REDUCE))
            {
                /* Ensure only one error message per statement */

                NextOp->Asl.CompileFlags |= OP_COULD_NOT_REDUCE;
                DbgPrint (ASL_PARSE_OUTPUT,
                    "**** Could not reduce operands for NAME opcode ****\n");

                AslError (ASL_ERROR, ASL_MSG_CONSTANT_REQUIRED, Op,
                    "Constant is required for Name operator");
                Status = AE_TYPE;
            }
        }

        if (ACPI_FAILURE (Status))
        {
            goto CleanupAndExit;
        }

        /* This is not a 3/4/5 opcode, but maybe can convert to STORE */

        if (Op->Asl.CompileFlags & OP_IS_TARGET)
        {
            DbgPrint (ASL_PARSE_OUTPUT,
                "**** Valid Target, transform to Store or CopyObject ****\n");
            return (AE_CTRL_RETURN_VALUE);
        }

        /* Expression cannot be reduced */

        DbgPrint (ASL_PARSE_OUTPUT,
            "**** Not a Type 3/4/5 opcode or cannot reduce/fold (%s) ****\n",
             Op->Asl.ParseOpName);

        Status = AE_TYPE;
        goto CleanupAndExit;
    }

    /*
     * TBD: Ignore buffer constants for now. The problem is that these
     * constants have been transformed into RAW_DATA at this point, from
     * the parse tree transform process which currently happens before
     * the constant folding process. We may need to defer this transform
     * for buffer until after the constant folding.
     */
    if (WalkState->Opcode == AML_BUFFER_OP)
    {
        DbgPrint (ASL_PARSE_OUTPUT,
            "\nBuffer constant reduction is currently not supported\n");

        if (NextOp) /* Found a Name() operator, error */
        {
            AslError (ASL_ERROR, ASL_MSG_UNSUPPORTED, Op,
                "Buffer expression cannot be reduced");
        }

        Status = AE_TYPE;
        goto CleanupAndExit;
    }

    /* Debug output */

    DbgPrint (ASL_PARSE_OUTPUT, "TYPE_345");

    if (Op->Asl.CompileFlags & OP_IS_TARGET)
    {
        if (Op->Asl.ParseOpcode == PARSEOP_ZERO)
        {
            DbgPrint (ASL_PARSE_OUTPUT, "%-16s", " NULL TARGET");
        }
        else
        {
            DbgPrint (ASL_PARSE_OUTPUT, "%-16s", " VALID TARGET");
        }
    }

    if (Op->Asl.CompileFlags & OP_IS_TERM_ARG)
    {
        DbgPrint (ASL_PARSE_OUTPUT, "%-16s", " TERMARG");
    }

CleanupAndExit:

    /* Dump the node compile flags also */

    TrPrintOpFlags (Op->Asl.CompileFlags, ASL_PARSE_OUTPUT);
    DbgPrint (ASL_PARSE_OUTPUT, "\n");
    return (Status);
}