#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_43__   TYPE_9__ ;
typedef  struct TYPE_42__   TYPE_8__ ;
typedef  struct TYPE_41__   TYPE_7__ ;
typedef  struct TYPE_40__   TYPE_6__ ;
typedef  struct TYPE_39__   TYPE_5__ ;
typedef  struct TYPE_38__   TYPE_4__ ;
typedef  struct TYPE_37__   TYPE_3__ ;
typedef  struct TYPE_36__   TYPE_2__ ;
typedef  struct TYPE_35__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_43__ {scalar_t__ Class; int Flags; } ;
struct TYPE_42__ {scalar_t__ PreviousAml; scalar_t__ StartAml; scalar_t__ AmlOffset; scalar_t__ LastLevel; int Count; scalar_t__ Level; int Flags; int /*<<< orphan*/  BitOffset; TYPE_2__* WalkState; } ;
struct TYPE_38__ {int /*<<< orphan*/  Name; } ;
struct TYPE_40__ {int AmlOpcode; scalar_t__ Aml; int DisasmFlags; scalar_t__ DisasmOpcode; TYPE_4__ Value; TYPE_7__* Next; TYPE_7__* Parent; } ;
struct TYPE_39__ {TYPE_7__* Parent; } ;
struct TYPE_37__ {int /*<<< orphan*/  Path; } ;
struct TYPE_41__ {TYPE_6__ Common; TYPE_5__ Asl; TYPE_3__ Named; } ;
struct TYPE_35__ {int /*<<< orphan*/  AmlStart; } ;
struct TYPE_36__ {TYPE_1__ ParserState; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_7__ ACPI_PARSE_OBJECT ;
typedef  TYPE_8__ ACPI_OP_WALK_INFO ;
typedef  TYPE_9__ ACPI_OPCODE_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_DASM_IGNORE_SINGLE ; 
 scalar_t__ ACPI_DASM_LNOT_PREFIX ; 
 scalar_t__ ACPI_DASM_RESOURCE ; 
 int ACPI_PARSEOP_ELSEIF ; 
 int ACPI_PARSEOP_IGNORE ; 
 int ACPI_PARSEOP_PARAMETER_LIST ; 
 scalar_t__ ACPI_PTR_DIFF (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_CTRL_DEPTH ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AMLCOMMENT_INLINE ; 
#define  AML_ALIAS_OP 149 
#define  AML_BANK_FIELD_OP 148 
#define  AML_BUFFER_OP 147 
 scalar_t__ AML_CLASS_CONTROL ; 
 scalar_t__ AML_CLASS_CREATE ; 
 scalar_t__ AML_CLASS_EXECUTE ; 
 scalar_t__ AML_CLASS_NAMED_OBJECT ; 
 int /*<<< orphan*/  AML_COMMENT_STANDARD ; 
#define  AML_DATA_REGION_OP 146 
#define  AML_DEVICE_OP 145 
#define  AML_EVENT_OP 144 
 scalar_t__ AML_EXTERNAL_OP ; 
#define  AML_FIELD_OP 143 
 int AML_HAS_ARGS ; 
#define  AML_IF_OP 142 
#define  AML_INDEX_FIELD_OP 141 
 scalar_t__ AML_INT_BYTELIST_OP ; 
 scalar_t__ AML_INT_CONNECTION_OP ; 
 int AML_INT_NAMEDFIELD_OP ; 
#define  AML_MATCH_OP 140 
#define  AML_METHOD_OP 139 
#define  AML_MUTEX_OP 138 
 int /*<<< orphan*/  AML_NAMECOMMENT ; 
 int AML_NAMED ; 
#define  AML_NAME_OP 137 
#define  AML_NOOP_OP 136 
#define  AML_PACKAGE_OP 135 
#define  AML_POWER_RESOURCE_OP 134 
#define  AML_PROCESSOR_OP 133 
#define  AML_REGION_OP 132 
 int AML_RETURN_OP ; 
#define  AML_SCOPE_OP 131 
#define  AML_THERMAL_ZONE_OP 130 
#define  AML_VARIABLE_PACKAGE_OP 129 
#define  AML_WHILE_OP 128 
 scalar_t__ AML_ZERO_OP ; 
 int /*<<< orphan*/  ASL_CV_CLOSE_PAREN (TYPE_7__*,scalar_t__) ; 
 scalar_t__ ASL_CV_FILE_HAS_SWITCHED (TYPE_7__*) ; 
 int /*<<< orphan*/  ASL_CV_LABEL_FILENODE (TYPE_7__*) ; 
 int /*<<< orphan*/  ASL_CV_PRINT_ONE_COMMENT (TYPE_7__*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ASL_CV_SWITCH_FILES (scalar_t__,TYPE_7__*) ; 
 int /*<<< orphan*/  AcpiDmAscendingOp ; 
 int AcpiDmBlockType (TYPE_7__*) ; 
 int /*<<< orphan*/  AcpiDmCheckForHardwareId (TYPE_7__*) ; 
 scalar_t__ AcpiDmCheckForSymbolicOpcode (TYPE_7__*,TYPE_8__*) ; 
 int /*<<< orphan*/  AcpiDmDisassembleOneOp (int /*<<< orphan*/ *,TYPE_8__*,TYPE_7__*) ; 
 int /*<<< orphan*/  AcpiDmDumpName (scalar_t__) ; 
 int /*<<< orphan*/  AcpiDmEmitExternals () ; 
 int /*<<< orphan*/  AcpiDmFieldFlags (TYPE_7__*) ; 
 int /*<<< orphan*/  AcpiDmIndent (scalar_t__) ; 
 int /*<<< orphan*/  AcpiDmMatchOp (TYPE_7__*) ; 
 int /*<<< orphan*/  AcpiDmMethodFlags (TYPE_7__*) ; 
 int /*<<< orphan*/  AcpiDmNamestring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmPredefinedDescription (TYPE_7__*) ; 
 int /*<<< orphan*/  AcpiDmRegionFlags (TYPE_7__*) ; 
 int /*<<< orphan*/  AcpiDmWalkParseTree (TYPE_7__*,int /*<<< orphan*/  (*) (TYPE_7__*,scalar_t__,void*),int /*<<< orphan*/ ,TYPE_8__*) ; 
 scalar_t__ AcpiGbl_CaptureComments ; 
 scalar_t__ AcpiGbl_CmSingleStep ; 
 int /*<<< orphan*/  AcpiGbl_DmEmitExternalOpcodes ; 
 scalar_t__ AcpiGbl_DmOpt_Listing ; 
 scalar_t__ AcpiGbl_DmOpt_Verbose ; 
 int /*<<< orphan*/  AcpiGbl_IgnoreNoopOperator ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 int /*<<< orphan*/  AcpiPsDisplayObjectPathname (int /*<<< orphan*/ *,TYPE_7__*) ; 
 TYPE_7__* AcpiPsGetDepthNext (int /*<<< orphan*/ *,TYPE_7__*) ; 
 scalar_t__ AcpiPsGetName (TYPE_7__*) ; 
 TYPE_9__* AcpiPsGetOpcodeInfo (int) ; 
 int /*<<< orphan*/  AcpiUtDumpBuffer (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int BLOCK_BRACE ; 
 int BLOCK_PAREN ; 
 int /*<<< orphan*/  DB_BYTE_DISPLAY ; 

__attribute__((used)) static ACPI_STATUS
AcpiDmDescendingOp (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{
    ACPI_OP_WALK_INFO       *Info = Context;
    const ACPI_OPCODE_INFO  *OpInfo;
    UINT32                  Name;
    ACPI_PARSE_OBJECT       *NextOp;
    ACPI_PARSE_OBJECT       *NextOp2;
    UINT32                  AmlOffset;


    /* Determine which file this parse node is contained in. */

    if (AcpiGbl_CaptureComments)
    {
        ASL_CV_LABEL_FILENODE (Op);

        if (Level != 0 && ASL_CV_FILE_HAS_SWITCHED (Op))
        {
            ASL_CV_SWITCH_FILES (Level, Op);
        }

        /* If this parse node has regular comments, print them here. */

        ASL_CV_PRINT_ONE_COMMENT (Op, AML_COMMENT_STANDARD, NULL, Level);
    }

    OpInfo = AcpiPsGetOpcodeInfo (Op->Common.AmlOpcode);

    /* Listing support to dump the AML code after the ASL statement */

    if (AcpiGbl_DmOpt_Listing)
    {
        /* We only care about these classes of objects */

        if ((OpInfo->Class == AML_CLASS_NAMED_OBJECT) ||
            (OpInfo->Class == AML_CLASS_CONTROL) ||
            (OpInfo->Class == AML_CLASS_CREATE) ||
            ((OpInfo->Class == AML_CLASS_EXECUTE) && (!Op->Common.Next)))
        {
            if (AcpiGbl_DmOpt_Listing && Info->PreviousAml)
            {
                /* Dump the AML byte code for the previous Op */

                if (Op->Common.Aml > Info->PreviousAml)
                {
                    AcpiOsPrintf ("\n");
                    AcpiUtDumpBuffer (
                        (Info->StartAml + Info->AmlOffset),
                        (Op->Common.Aml - Info->PreviousAml),
                        DB_BYTE_DISPLAY, Info->AmlOffset);
                    AcpiOsPrintf ("\n");
                }

                Info->AmlOffset = (Op->Common.Aml - Info->StartAml);
            }

            Info->PreviousAml = Op->Common.Aml;
        }
    }

    if (Op->Common.DisasmFlags & ACPI_PARSEOP_IGNORE)
    {
        /* Ignore this op -- it was handled elsewhere */

        return (AE_CTRL_DEPTH);
    }

    if (Op->Common.DisasmOpcode == ACPI_DASM_IGNORE_SINGLE)
    {
        /* Ignore this op, but not it's children */

        return (AE_OK);
    }

    if (Op->Common.AmlOpcode == AML_IF_OP)
    {
        NextOp = AcpiPsGetDepthNext (NULL, Op);
        if (NextOp)
        {
            NextOp->Common.DisasmFlags |= ACPI_PARSEOP_PARAMETER_LIST;

            /* Don't emit the actual embedded externals unless asked */

            if (!AcpiGbl_DmEmitExternalOpcodes)
            {
                /*
                 * A Zero predicate indicates the possibility of one or more
                 * External() opcodes within the If() block.
                 */
                if (NextOp->Common.AmlOpcode == AML_ZERO_OP)
                {
                    NextOp2 = NextOp->Common.Next;

                    if (NextOp2 &&
                        (NextOp2->Common.AmlOpcode == AML_EXTERNAL_OP))
                    {
                        /* Ignore the If 0 block and all children */

                        Op->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;
                        return (AE_CTRL_DEPTH);
                    }
                }
            }
        }
    }

    /* Level 0 is at the Definition Block level */

    if (Level == 0)
    {
        /* In verbose mode, print the AML offset, opcode and depth count */

        if (Info->WalkState)
        {
            AmlOffset = (UINT32) ACPI_PTR_DIFF (Op->Common.Aml,
                Info->WalkState->ParserState.AmlStart);
            if (AcpiGbl_DmOpt_Verbose)
            {
                if (AcpiGbl_CmSingleStep)
                {
                    AcpiOsPrintf ("%5.5X/%4.4X: ",
                        AmlOffset, (UINT32) Op->Common.AmlOpcode);
                }
                else
                {
                    AcpiOsPrintf ("AML Offset %5.5X, Opcode %4.4X: ",
                        AmlOffset, (UINT32) Op->Common.AmlOpcode);
                }
            }
        }

        if (Op->Common.AmlOpcode == AML_SCOPE_OP)
        {
            /* This is the beginning of the Definition Block */

            AcpiOsPrintf ("{\n");

            /* Emit all External() declarations here */

            if (!AcpiGbl_DmEmitExternalOpcodes)
            {
                AcpiDmEmitExternals ();
            }

            return (AE_OK);
        }
    }
    else if ((AcpiDmBlockType (Op->Common.Parent) & BLOCK_BRACE) &&
         (!(Op->Common.DisasmFlags & ACPI_PARSEOP_PARAMETER_LIST)) &&
         (!(Op->Common.DisasmFlags & ACPI_PARSEOP_ELSEIF)) &&
         (Op->Common.AmlOpcode != AML_INT_BYTELIST_OP))
    {
        /*
         * This is a first-level element of a term list,
         * indent a new line
         */
        switch (Op->Common.AmlOpcode)
        {
        case AML_NOOP_OP:
            /*
             * Optionally just ignore this opcode. Some tables use
             * NoOp opcodes for "padding" out packages that the BIOS
             * changes dynamically. This can leave hundreds or
             * thousands of NoOp opcodes that if disassembled,
             * cannot be compiled because they are syntactically
             * incorrect.
             */
            if (AcpiGbl_IgnoreNoopOperator)
            {
                Op->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;
                return (AE_OK);
            }

            /* Fallthrough */

        default:

            AcpiDmIndent (Level);
            break;
        }

        Info->LastLevel = Level;
        Info->Count = 0;
    }

    /*
     * This is an inexpensive mechanism to try and keep lines from getting
     * too long. When the limit is hit, start a new line at the previous
     * indent plus one. A better but more expensive mechanism would be to
     * keep track of the current column.
     */
    Info->Count++;
    if (Info->Count /* +Info->LastLevel */ > 12)
    {
        Info->Count = 0;
        AcpiOsPrintf ("\n");
        AcpiDmIndent (Info->LastLevel + 1);
    }

    /* If ASL+ is enabled, check for a C-style operator */

    if (AcpiDmCheckForSymbolicOpcode (Op, Info))
    {
        return (AE_OK);
    }

    /* Print the opcode name */

    AcpiDmDisassembleOneOp (NULL, Info, Op);

    if ((Op->Common.DisasmOpcode == ACPI_DASM_LNOT_PREFIX) ||
        (Op->Common.AmlOpcode == AML_INT_CONNECTION_OP))
    {
        return (AE_OK);
    }

    if ((Op->Common.AmlOpcode == AML_NAME_OP) ||
        (Op->Common.AmlOpcode == AML_RETURN_OP))
    {
        Info->Level--;
    }

    if (Op->Common.AmlOpcode == AML_EXTERNAL_OP)
    {
        Op->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;
        return (AE_CTRL_DEPTH);
    }

    /* Start the opcode argument list if necessary */

    if ((OpInfo->Flags & AML_HAS_ARGS) ||
        (Op->Common.AmlOpcode == AML_EVENT_OP))
    {
        /* This opcode has an argument list */

        if (AcpiDmBlockType (Op) & BLOCK_PAREN)
        {
            AcpiOsPrintf (" (");
            if (!(AcpiDmBlockType (Op) & BLOCK_BRACE))
            {
                ASL_CV_PRINT_ONE_COMMENT (Op, AMLCOMMENT_INLINE, " ", 0);
            }
        }

        /* If this is a named opcode, print the associated name value */

        if (OpInfo->Flags & AML_NAMED)
        {
            switch (Op->Common.AmlOpcode)
            {
            case AML_ALIAS_OP:

                NextOp = AcpiPsGetDepthNext (NULL, Op);
                NextOp->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;
                AcpiDmNamestring (NextOp->Common.Value.Name);
                AcpiOsPrintf (", ");

                /*lint -fallthrough */

            default:

                Name = AcpiPsGetName (Op);
                if (Op->Named.Path)
                {
                    AcpiDmNamestring (Op->Named.Path);
                }
                else
                {
                    AcpiDmDumpName (Name);
                }

                if (Op->Common.AmlOpcode != AML_INT_NAMEDFIELD_OP)
                {
                    if (AcpiGbl_DmOpt_Verbose)
                    {
                        (void) AcpiPsDisplayObjectPathname (NULL, Op);
                    }
                }
                break;
            }

            switch (Op->Common.AmlOpcode)
            {
            case AML_METHOD_OP:

                AcpiDmMethodFlags (Op);
                ASL_CV_CLOSE_PAREN (Op, Level);

                /* Emit description comment for Method() with a predefined ACPI name */

                AcpiDmPredefinedDescription (Op);
                break;

            case AML_NAME_OP:

                /* Check for _HID and related EISAID() */

                AcpiDmCheckForHardwareId (Op);
                AcpiOsPrintf (", ");
                ASL_CV_PRINT_ONE_COMMENT (Op, AML_NAMECOMMENT, NULL, 0);
                break;

            case AML_REGION_OP:

                AcpiDmRegionFlags (Op);
                break;

            case AML_POWER_RESOURCE_OP:

                /* Mark the next two Ops as part of the parameter list */

                AcpiOsPrintf (", ");
                NextOp = AcpiPsGetDepthNext (NULL, Op);
                NextOp->Common.DisasmFlags |= ACPI_PARSEOP_PARAMETER_LIST;

                NextOp = NextOp->Common.Next;
                NextOp->Common.DisasmFlags |= ACPI_PARSEOP_PARAMETER_LIST;
                return (AE_OK);

            case AML_PROCESSOR_OP:

                /* Mark the next three Ops as part of the parameter list */

                AcpiOsPrintf (", ");
                NextOp = AcpiPsGetDepthNext (NULL, Op);
                NextOp->Common.DisasmFlags |= ACPI_PARSEOP_PARAMETER_LIST;

                NextOp = NextOp->Common.Next;
                NextOp->Common.DisasmFlags |= ACPI_PARSEOP_PARAMETER_LIST;

                NextOp = NextOp->Common.Next;
                NextOp->Common.DisasmFlags |= ACPI_PARSEOP_PARAMETER_LIST;
                return (AE_OK);

            case AML_MUTEX_OP:
            case AML_DATA_REGION_OP:

                AcpiOsPrintf (", ");
                return (AE_OK);

            case AML_EVENT_OP:
            case AML_ALIAS_OP:

                return (AE_OK);

            case AML_SCOPE_OP:
            case AML_DEVICE_OP:
            case AML_THERMAL_ZONE_OP:

                ASL_CV_CLOSE_PAREN (Op, Level);
                break;

            default:

                AcpiOsPrintf ("*** Unhandled named opcode %X\n",
                    Op->Common.AmlOpcode);
                break;
            }
        }

        else switch (Op->Common.AmlOpcode)
        {
        case AML_FIELD_OP:
        case AML_BANK_FIELD_OP:
        case AML_INDEX_FIELD_OP:

            Info->BitOffset = 0;

            /* Name of the parent OperationRegion */

            NextOp = AcpiPsGetDepthNext (NULL, Op);
            AcpiDmNamestring (NextOp->Common.Value.Name);
            AcpiOsPrintf (", ");
            NextOp->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;

            switch (Op->Common.AmlOpcode)
            {
            case AML_BANK_FIELD_OP:

                /* Namestring - Bank Name */

                NextOp = AcpiPsGetDepthNext (NULL, NextOp);
                AcpiDmNamestring (NextOp->Common.Value.Name);
                NextOp->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;
                AcpiOsPrintf (", ");

                /*
                 * Bank Value. This is a TermArg in the middle of the parameter
                 * list, must handle it here.
                 *
                 * Disassemble the TermArg parse tree. ACPI_PARSEOP_PARAMETER_LIST
                 * eliminates newline in the output.
                 */
                NextOp = NextOp->Common.Next;

                Info->Flags = ACPI_PARSEOP_PARAMETER_LIST;
                AcpiDmWalkParseTree (NextOp, AcpiDmDescendingOp,
                    AcpiDmAscendingOp, Info);
                Info->Flags = 0;
                Info->Level = Level;

                NextOp->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;
                AcpiOsPrintf (", ");
                break;

            case AML_INDEX_FIELD_OP:

                /* Namestring - Data Name */

                NextOp = AcpiPsGetDepthNext (NULL, NextOp);
                AcpiDmNamestring (NextOp->Common.Value.Name);
                AcpiOsPrintf (", ");
                NextOp->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;
                break;

            default:

                break;
            }

            AcpiDmFieldFlags (NextOp);
            break;

        case AML_BUFFER_OP:

            /* The next op is the size parameter */

            NextOp = AcpiPsGetDepthNext (NULL, Op);
            if (!NextOp)
            {
                /* Single-step support */

                return (AE_OK);
            }

            if (Op->Common.DisasmOpcode == ACPI_DASM_RESOURCE)
            {
                /*
                 * We have a resource list. Don't need to output
                 * the buffer size Op. Open up a new block
                 */
                NextOp->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;
                ASL_CV_CLOSE_PAREN (Op, Level);

                /* Emit description comment for Name() with a predefined ACPI name */

                AcpiDmPredefinedDescription (Op->Asl.Parent);

                AcpiOsPrintf ("\n");
                AcpiDmIndent (Info->Level);
                AcpiOsPrintf ("{\n");
                return (AE_OK);
            }

            /* Normal Buffer, mark size as in the parameter list */

            NextOp->Common.DisasmFlags |= ACPI_PARSEOP_PARAMETER_LIST;
            return (AE_OK);

        case AML_IF_OP:
        case AML_VARIABLE_PACKAGE_OP:
        case AML_WHILE_OP:

            /* The next op is the size or predicate parameter */

            NextOp = AcpiPsGetDepthNext (NULL, Op);
            if (NextOp)
            {
                NextOp->Common.DisasmFlags |= ACPI_PARSEOP_PARAMETER_LIST;
            }
            return (AE_OK);

        case AML_PACKAGE_OP:

            /* The next op is the size parameter */

            NextOp = AcpiPsGetDepthNext (NULL, Op);
            if (NextOp)
            {
                NextOp->Common.DisasmFlags |= ACPI_PARSEOP_PARAMETER_LIST;
            }
            return (AE_OK);

        case AML_MATCH_OP:

            AcpiDmMatchOp (Op);
            break;

        default:

            break;
        }

        if (AcpiDmBlockType (Op) & BLOCK_BRACE)
        {
            AcpiOsPrintf ("\n");
            AcpiDmIndent (Level);
            AcpiOsPrintf ("{\n");
        }
    }

    return (AE_OK);
}