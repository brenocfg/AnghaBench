#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_9__ ;
typedef  struct TYPE_41__   TYPE_8__ ;
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_1__ ;
typedef  struct TYPE_33__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  size_t UINT32 ;
struct TYPE_42__ {size_t BitOffset; int Level; TYPE_8__* MappingOp; } ;
struct TYPE_37__ {int Integer; int /*<<< orphan*/  Name; TYPE_8__* Arg; int /*<<< orphan*/  String; } ;
struct TYPE_38__ {int DisasmFlags; int DisasmOpcode; int AmlOpcode; TYPE_4__ Value; int /*<<< orphan*/  Parent; } ;
struct TYPE_34__ {int /*<<< orphan*/ * Data; int /*<<< orphan*/  Name; } ;
struct TYPE_41__ {TYPE_5__ Common; TYPE_1__ Named; } ;
struct TYPE_40__ {int /*<<< orphan*/  ResultCount; TYPE_3__* Results; } ;
struct TYPE_39__ {char* Description; } ;
struct TYPE_35__ {int /*<<< orphan*/ * ObjDesc; } ;
struct TYPE_36__ {TYPE_2__ Results; } ;
struct TYPE_33__ {char* Name; } ;
typedef  TYPE_6__ AH_DEVICE_ID ;
typedef  TYPE_7__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_8__ ACPI_PARSE_OBJECT ;
typedef  TYPE_9__ ACPI_OP_WALK_INFO ;
typedef  TYPE_10__ ACPI_OPCODE_INFO ;

/* Variables and functions */
 int ACPI_DASM_BUFFER ; 
 int ACPI_DASM_CASE ; 
 int ACPI_DASM_EISAID ; 
 int ACPI_DASM_HID_STRING ; 
 int ACPI_DASM_LNOT_PREFIX ; 
#define  ACPI_DASM_LNOT_SUFFIX 151 
#define  ACPI_DASM_MATCHOP 150 
 int ACPI_DASM_PLD_METHOD ; 
 void* ACPI_DASM_RESOURCE ; 
 int ACPI_DASM_STRING ; 
 int ACPI_DASM_SWITCH ; 
 int ACPI_DASM_UNICODE ; 
 int ACPI_DASM_UUID ; 
 char* ACPI_DIV_8 (int) ; 
 char* ACPI_FORMAT_UINT64 (int) ; 
 int ACPI_PARSEOP_ELSEIF ; 
 int ACPI_PARSEOP_IGNORE ; 
 size_t ACPI_RESULTS_FRAME_OBJ_NUM ; 
 int /*<<< orphan*/  ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_UINT16_MAX ; 
 int /*<<< orphan*/  AE_AML_NO_RESOURCE_END_TAG ; 
 int /*<<< orphan*/  AMLCOMMENT_INLINE ; 
#define  AML_BUFFER_OP 149 
#define  AML_BYTE_OP 148 
 int /*<<< orphan*/  AML_COMMENT_END_NODE ; 
#define  AML_DWORD_OP 147 
#define  AML_ELSE_OP 146 
#define  AML_EXTERNAL_OP 145 
#define  AML_IF_OP 144 
#define  AML_INT_ACCESSFIELD_OP 143 
#define  AML_INT_BYTELIST_OP 142 
#define  AML_INT_CONNECTION_OP 141 
#define  AML_INT_EXTACCESSFIELD_OP 140 
#define  AML_INT_METHODCALL_OP 139 
#define  AML_INT_NAMEDFIELD_OP 138 
#define  AML_INT_NAMEPATH_OP 137 
#define  AML_INT_RESERVEDFIELD_OP 136 
 int AML_INT_RETURN_VALUE_OP ; 
#define  AML_LOGICAL_EQUAL_OP 135 
#define  AML_LOGICAL_GREATER_OP 134 
#define  AML_LOGICAL_LESS_OP 133 
#define  AML_LOGICAL_NOT_OP 132 
 int /*<<< orphan*/  AML_NAMECOMMENT ; 
#define  AML_QWORD_OP 131 
#define  AML_STRING_OP 130 
#define  AML_WHILE_OP 129 
#define  AML_WORD_OP 128 
 int /*<<< orphan*/  ASL_CV_PRINT_ONE_COMMENT (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_6__* AcpiAhMatchHardwareId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDbDecodeInternalObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmByteList (TYPE_9__*,TYPE_8__*) ; 
 int /*<<< orphan*/  AcpiDmCommaIfFieldMember (TYPE_8__*) ; 
 int /*<<< orphan*/  AcpiDmConvertToElseIf (TYPE_8__*) ; 
 int /*<<< orphan*/  AcpiDmDecodeAttribute (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmDecompressEisaId (size_t) ; 
 size_t AcpiDmDumpName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmEmitExternal (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmIndent (int) ; 
 int /*<<< orphan*/  AcpiDmIsPldBuffer (TYPE_8__*) ; 
 int /*<<< orphan*/  AcpiDmIsResourceTemplate (TYPE_7__*,TYPE_8__*) ; 
 int /*<<< orphan*/  AcpiDmIsStringBuffer (TYPE_8__*) ; 
 int /*<<< orphan*/  AcpiDmIsUnicodeBuffer (TYPE_8__*) ; 
 int /*<<< orphan*/  AcpiDmIsUuidBuffer (TYPE_8__*) ; 
 int /*<<< orphan*/  AcpiDmMatchKeyword (TYPE_8__*) ; 
 int /*<<< orphan*/  AcpiDmNamestring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmResourceTemplate (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 char** AcpiGbl_AccessTypes ; 
 int /*<<< orphan*/  AcpiGbl_CstyleDisassembly ; 
 int /*<<< orphan*/  AcpiGbl_DmEmitExternalOpcodes ; 
 int /*<<< orphan*/  AcpiGbl_NoResourceDisassembly ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 int /*<<< orphan*/  AcpiPsGetArg (TYPE_8__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* AcpiPsGetDepthNext (int /*<<< orphan*/ *,TYPE_8__*) ; 
 TYPE_10__* AcpiPsGetOpcodeInfo (int) ; 
 int /*<<< orphan*/  AcpiUtPrintString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
AcpiDmDisassembleOneOp (
    ACPI_WALK_STATE         *WalkState,
    ACPI_OP_WALK_INFO       *Info,
    ACPI_PARSE_OBJECT       *Op)
{
    const ACPI_OPCODE_INFO  *OpInfo = NULL;
    UINT32                  Offset;
    UINT32                  Length;
    ACPI_PARSE_OBJECT       *Child;
    ACPI_STATUS             Status;
    UINT8                   *Aml;
    const AH_DEVICE_ID      *IdInfo;


    if (!Op)
    {
        AcpiOsPrintf ("<NULL OP PTR>");
        return;
    }

    if (Op->Common.DisasmFlags & ACPI_PARSEOP_ELSEIF)
    {
        return; /* ElseIf macro was already emitted */
    }

    switch (Op->Common.DisasmOpcode)
    {
    case ACPI_DASM_MATCHOP:

        AcpiDmMatchKeyword (Op);
        return;

    case ACPI_DASM_LNOT_SUFFIX:

        if (!AcpiGbl_CstyleDisassembly)
        {
            switch (Op->Common.AmlOpcode)
            {
            case AML_LOGICAL_EQUAL_OP:
                AcpiOsPrintf ("LNotEqual");
                break;

            case AML_LOGICAL_GREATER_OP:
                AcpiOsPrintf ("LLessEqual");
                break;

            case AML_LOGICAL_LESS_OP:
                AcpiOsPrintf ("LGreaterEqual");
                break;

            default:
                break;
            }
        }

        Op->Common.DisasmOpcode = 0;
        Op->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;
        return;

    default:
        break;
    }

    OpInfo = AcpiPsGetOpcodeInfo (Op->Common.AmlOpcode);

    /* The op and arguments */

    switch (Op->Common.AmlOpcode)
    {
    case AML_LOGICAL_NOT_OP:

        Child = Op->Common.Value.Arg;
        if ((Child->Common.AmlOpcode == AML_LOGICAL_EQUAL_OP) ||
            (Child->Common.AmlOpcode == AML_LOGICAL_GREATER_OP) ||
            (Child->Common.AmlOpcode == AML_LOGICAL_LESS_OP))
        {
            Child->Common.DisasmOpcode = ACPI_DASM_LNOT_SUFFIX;
            Op->Common.DisasmOpcode = ACPI_DASM_LNOT_PREFIX;
        }
        else
        {
            AcpiOsPrintf ("%s", OpInfo->Name);
        }
        break;

    case AML_BYTE_OP:

        AcpiOsPrintf ("0x%2.2X", (UINT32) Op->Common.Value.Integer);
        break;

    case AML_WORD_OP:

        if (Op->Common.DisasmOpcode == ACPI_DASM_EISAID)
        {
            AcpiDmDecompressEisaId ((UINT32) Op->Common.Value.Integer);
        }
        else
        {
            AcpiOsPrintf ("0x%4.4X", (UINT32) Op->Common.Value.Integer);
        }
        break;

    case AML_DWORD_OP:

        if (Op->Common.DisasmOpcode == ACPI_DASM_EISAID)
        {
            AcpiDmDecompressEisaId ((UINT32) Op->Common.Value.Integer);
        }
        else
        {
            AcpiOsPrintf ("0x%8.8X", (UINT32) Op->Common.Value.Integer);
        }
        break;

    case AML_QWORD_OP:

        AcpiOsPrintf ("0x%8.8X%8.8X",
            ACPI_FORMAT_UINT64 (Op->Common.Value.Integer));
        break;

    case AML_STRING_OP:

        AcpiUtPrintString (Op->Common.Value.String, ACPI_UINT16_MAX);

        /* For _HID/_CID strings, attempt to output a descriptive comment */

        if (Op->Common.DisasmOpcode == ACPI_DASM_HID_STRING)
        {
            /* If we know about the ID, emit the description */

            IdInfo = AcpiAhMatchHardwareId (Op->Common.Value.String);
            if (IdInfo)
            {
                AcpiOsPrintf (" /* %s */", IdInfo->Description);
            }
        }
        break;

    case AML_BUFFER_OP:
        /*
         * Determine the type of buffer. We can have one of the following:
         *
         * 1) ResourceTemplate containing Resource Descriptors.
         * 2) Unicode String buffer
         * 3) ASCII String buffer
         * 4) Raw data buffer (if none of the above)
         *
         * Since there are no special AML opcodes to differentiate these
         * types of buffers, we have to closely look at the data in the
         * buffer to determine the type.
         */
        if (!AcpiGbl_NoResourceDisassembly)
        {
            Status = AcpiDmIsResourceTemplate (WalkState, Op);
            if (ACPI_SUCCESS (Status))
            {
                Op->Common.DisasmOpcode = ACPI_DASM_RESOURCE;
                AcpiOsPrintf ("ResourceTemplate");
                break;
            }
            else if (Status == AE_AML_NO_RESOURCE_END_TAG)
            {
                AcpiOsPrintf (
                    "/**** Is ResourceTemplate, "
                    "but EndTag not at buffer end ****/ ");
            }
        }

        if (AcpiDmIsUuidBuffer (Op))
        {
            Op->Common.DisasmOpcode = ACPI_DASM_UUID;
            AcpiOsPrintf ("ToUUID (");
        }
        else if (AcpiDmIsUnicodeBuffer (Op))
        {
            Op->Common.DisasmOpcode = ACPI_DASM_UNICODE;
            AcpiOsPrintf ("Unicode (");
        }
        else if (AcpiDmIsStringBuffer (Op))
        {
            Op->Common.DisasmOpcode = ACPI_DASM_STRING;
            AcpiOsPrintf ("Buffer");
        }
        else if (AcpiDmIsPldBuffer (Op))
        {
            Op->Common.DisasmOpcode = ACPI_DASM_PLD_METHOD;
            AcpiOsPrintf ("ToPLD (");
        }
        else
        {
            Op->Common.DisasmOpcode = ACPI_DASM_BUFFER;
            AcpiOsPrintf ("Buffer");
        }
        break;

    case AML_INT_NAMEPATH_OP:

        AcpiDmNamestring (Op->Common.Value.Name);
        break;

    case AML_INT_NAMEDFIELD_OP:

        Length = AcpiDmDumpName (Op->Named.Name);

        AcpiOsPrintf (",");
        ASL_CV_PRINT_ONE_COMMENT (Op, AML_NAMECOMMENT, NULL, 0);
        AcpiOsPrintf ("%*.s  %u", (unsigned) (5 - Length), " ",
            (UINT32) Op->Common.Value.Integer);

        AcpiDmCommaIfFieldMember (Op);

        Info->BitOffset += (UINT32) Op->Common.Value.Integer;
        break;

    case AML_INT_RESERVEDFIELD_OP:

        /* Offset() -- Must account for previous offsets */

        Offset = (UINT32) Op->Common.Value.Integer;
        Info->BitOffset += Offset;

        if (Info->BitOffset % 8 == 0)
        {
            AcpiOsPrintf ("Offset (0x%.2X)", ACPI_DIV_8 (Info->BitOffset));
        }
        else
        {
            AcpiOsPrintf ("    ,   %u", Offset);
        }

        AcpiDmCommaIfFieldMember (Op);
        break;

    case AML_INT_ACCESSFIELD_OP:
    case AML_INT_EXTACCESSFIELD_OP:

        AcpiOsPrintf ("AccessAs (%s, ",
            AcpiGbl_AccessTypes [(UINT32) (Op->Common.Value.Integer & 0x7)]);

        AcpiDmDecodeAttribute ((UINT8) (Op->Common.Value.Integer >> 8));

        if (Op->Common.AmlOpcode == AML_INT_EXTACCESSFIELD_OP)
        {
            AcpiOsPrintf (" (0x%2.2X)", (unsigned)
                ((Op->Common.Value.Integer >> 16) & 0xFF));
        }

        AcpiOsPrintf (")");
        AcpiDmCommaIfFieldMember (Op);
        ASL_CV_PRINT_ONE_COMMENT (Op, AML_COMMENT_END_NODE, NULL, 0);
        break;

    case AML_INT_CONNECTION_OP:
        /*
         * Two types of Connection() - one with a buffer object, the
         * other with a namestring that points to a buffer object.
         */
        AcpiOsPrintf ("Connection (");
        Child = Op->Common.Value.Arg;

        if (Child->Common.AmlOpcode == AML_INT_BYTELIST_OP)
        {
            AcpiOsPrintf ("\n");

            Aml = Child->Named.Data;
            Length = (UINT32) Child->Common.Value.Integer;

            Info->Level += 1;
            Info->MappingOp = Op;
            Op->Common.DisasmOpcode = ACPI_DASM_RESOURCE;

            AcpiDmResourceTemplate (Info, Op->Common.Parent, Aml, Length);

            Info->Level -= 1;
            AcpiDmIndent (Info->Level);
        }
        else
        {
            AcpiDmNamestring (Child->Common.Value.Name);
        }

        AcpiOsPrintf (")");
        AcpiDmCommaIfFieldMember (Op);
        ASL_CV_PRINT_ONE_COMMENT (Op, AML_COMMENT_END_NODE, NULL, 0);
        ASL_CV_PRINT_ONE_COMMENT (Op, AMLCOMMENT_INLINE, NULL, 0);
        AcpiOsPrintf ("\n");

        Op->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE; /* for now, ignore in AcpiDmAscendingOp */
        Child->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;
        break;

    case AML_INT_BYTELIST_OP:

        AcpiDmByteList (Info, Op);
        break;

    case AML_INT_METHODCALL_OP:

        Op = AcpiPsGetDepthNext (NULL, Op);
        Op->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;

        AcpiDmNamestring (Op->Common.Value.Name);
        break;

    case AML_WHILE_OP:

        if (Op->Common.DisasmOpcode == ACPI_DASM_SWITCH)
        {
            AcpiOsPrintf ("%s", "Switch");
            break;
        }

        AcpiOsPrintf ("%s", OpInfo->Name);
        break;

    case AML_IF_OP:

        if (Op->Common.DisasmOpcode == ACPI_DASM_CASE)
        {
            AcpiOsPrintf ("%s", "Case");
            break;
        }

        AcpiOsPrintf ("%s", OpInfo->Name);
        break;

    case AML_ELSE_OP:

        AcpiDmConvertToElseIf (Op);
        break;

    case AML_EXTERNAL_OP:

        if (AcpiGbl_DmEmitExternalOpcodes)
        {
            AcpiDmEmitExternal (Op, AcpiPsGetArg(Op, 0));
        }

        break;

    default:

        /* Just get the opcode name and print it */

        AcpiOsPrintf ("%s", OpInfo->Name);


#ifdef ACPI_DEBUGGER

        if ((Op->Common.AmlOpcode == AML_INT_RETURN_VALUE_OP) &&
            (WalkState) &&
            (WalkState->Results) &&
            (WalkState->ResultCount))
        {
            AcpiDbDecodeInternalObject (
                WalkState->Results->Results.ObjDesc [
                    (WalkState->ResultCount - 1) %
                        ACPI_RESULTS_FRAME_OBJ_NUM]);
        }
#endif

        break;
    }
}