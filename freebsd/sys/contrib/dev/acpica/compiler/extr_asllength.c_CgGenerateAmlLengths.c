#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_8__ {char* String; int /*<<< orphan*/  Integer; } ;
struct TYPE_9__ {int AmlOpcode; int AmlOpcodeLength; int AmlLength; int ParseOpcode; char* ExternalName; int CompileFlags; TYPE_1__ Value; int /*<<< orphan*/  AmlPkgLenBytes; int /*<<< orphan*/  AmlSubtreeLength; } ;
struct TYPE_10__ {TYPE_2__ Asl; } ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
#define  AML_RAW_DATA_BUFFER 144 
#define  AML_RAW_DATA_BYTE 143 
#define  AML_RAW_DATA_CHAIN 142 
#define  AML_RAW_DATA_DWORD 141 
#define  AML_RAW_DATA_QWORD 140 
#define  AML_RAW_DATA_WORD 139 
 int /*<<< orphan*/  ASL_DEBUG_OUTPUT ; 
 int /*<<< orphan*/  AslGbl_TableLength ; 
 int /*<<< orphan*/  CgGenerateAmlOpcodeLength (TYPE_3__*) ; 
 int /*<<< orphan*/  CgGetPackageLenByteCount (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int OP_NAME_INTERNALIZED ; 
#define  PARSEOP_DEFAULT_ARG 138 
#define  PARSEOP_DEFINITION_BLOCK 137 
#define  PARSEOP_EXTERNAL 136 
#define  PARSEOP_INCLUDE 135 
#define  PARSEOP_INCLUDE_END 134 
#define  PARSEOP_METHODCALL 133 
#define  PARSEOP_NAMESEG 132 
#define  PARSEOP_NAMESTRING 131 
#define  PARSEOP_PACKAGE_LENGTH 130 
#define  PARSEOP_RAW_DATA 129 
#define  PARSEOP_STRING_LITERAL 128 
 int /*<<< orphan*/  UtInternalizeName (char*,char**) ; 
 int /*<<< orphan*/  UtNameContainsAllPrefix (TYPE_3__*) ; 
 int strlen (char*) ; 

void
CgGenerateAmlLengths (
    ACPI_PARSE_OBJECT       *Op)
{
    char                    *Buffer;
    ACPI_STATUS             Status;


    switch (Op->Asl.AmlOpcode)
    {
    case AML_RAW_DATA_BYTE:

        Op->Asl.AmlOpcodeLength = 0;
        Op->Asl.AmlLength = 1;
        return;

    case AML_RAW_DATA_WORD:

        Op->Asl.AmlOpcodeLength = 0;
        Op->Asl.AmlLength = 2;
        return;

    case AML_RAW_DATA_DWORD:

        Op->Asl.AmlOpcodeLength = 0;
        Op->Asl.AmlLength = 4;
        return;

    case AML_RAW_DATA_QWORD:

        Op->Asl.AmlOpcodeLength = 0;
        Op->Asl.AmlLength = 8;
        return;

    case AML_RAW_DATA_BUFFER:

        /* Aml length is/was set by creator */

        Op->Asl.AmlOpcodeLength = 0;
        return;

    case AML_RAW_DATA_CHAIN:

        /* Aml length is/was set by creator */

        Op->Asl.AmlOpcodeLength = 0;
        return;

    default:

        break;
    }

    switch (Op->Asl.ParseOpcode)
    {
    case PARSEOP_DEFINITION_BLOCK:

        AslGbl_TableLength = sizeof (ACPI_TABLE_HEADER) + Op->Asl.AmlSubtreeLength;
        break;

    case PARSEOP_NAMESEG:

        Op->Asl.AmlOpcodeLength = 0;
        Op->Asl.AmlLength = 4;
        Op->Asl.ExternalName = Op->Asl.Value.String;
        break;

    case PARSEOP_NAMESTRING:
    case PARSEOP_METHODCALL:

        if (Op->Asl.CompileFlags & OP_NAME_INTERNALIZED)
        {
            break;
        }

        Op->Asl.AmlOpcodeLength = 0;
        Status = UtInternalizeName (Op->Asl.Value.String, &Buffer);
        if (ACPI_FAILURE (Status))
        {
            DbgPrint (ASL_DEBUG_OUTPUT,
                "Failure from internalize name %X\n", Status);
            break;
        }

        Op->Asl.ExternalName = Op->Asl.Value.String;
        Op->Asl.Value.String = Buffer;
        Op->Asl.CompileFlags |= OP_NAME_INTERNALIZED;
        Op->Asl.AmlLength = strlen (Buffer);

        /*
         * Check for single backslash reference to root or reference to a name
         * consisting of only prefix (^) characters. Make it a null terminated
         * string in the AML.
         */
        if (Op->Asl.AmlLength == 1 || UtNameContainsAllPrefix(Op))
        {
            Op->Asl.AmlLength++;
        }
        break;

    case PARSEOP_STRING_LITERAL:

        Op->Asl.AmlOpcodeLength = 1;

        /* Get null terminator */

        Op->Asl.AmlLength = strlen (Op->Asl.Value.String) + 1;
        break;

    case PARSEOP_PACKAGE_LENGTH:

        Op->Asl.AmlOpcodeLength = 0;
        Op->Asl.AmlPkgLenBytes = CgGetPackageLenByteCount (Op,
            (UINT32) Op->Asl.Value.Integer);
        break;

    case PARSEOP_RAW_DATA:

        Op->Asl.AmlOpcodeLength = 0;
        break;

    case PARSEOP_DEFAULT_ARG:
    case PARSEOP_INCLUDE:
    case PARSEOP_INCLUDE_END:

        /* Ignore the "default arg" nodes, they are extraneous at this point */

        break;

    case PARSEOP_EXTERNAL:

        CgGenerateAmlOpcodeLength (Op);
        break;

    default:

        CgGenerateAmlOpcodeLength (Op);
        break;
    }
}