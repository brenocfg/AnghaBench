#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
typedef  size_t UINT16 ;
struct TYPE_17__ {int /*<<< orphan*/  Integer; } ;
struct TYPE_18__ {int ParseOpcode; int AmlOpcodeLength; TYPE_1__ Value; int /*<<< orphan*/  CompileFlags; int /*<<< orphan*/  AcpiBtype; int /*<<< orphan*/  AmlOpcode; } ;
struct TYPE_19__ {TYPE_2__ Asl; } ;
struct TYPE_16__ {int /*<<< orphan*/  Value; int /*<<< orphan*/  Flags; int /*<<< orphan*/  AcpiBtype; int /*<<< orphan*/  AmlOpcode; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_MSG_TRUNCATION ; 
 scalar_t__ ASL_PARSE_OPCODE_BASE ; 
 int /*<<< orphan*/  ASL_REMARK ; 
 int AcpiGbl_IntegerBitWidth ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AslGbl_HasIncludeFiles ; 
 TYPE_14__* AslKeywordMapping ; 
 int /*<<< orphan*/  OpcDoAccessAs (TYPE_3__*) ; 
 int /*<<< orphan*/  OpcDoConnection (TYPE_3__*) ; 
 int /*<<< orphan*/  OpcDoEisaId (TYPE_3__*) ; 
 int /*<<< orphan*/  OpcDoFprintf (TYPE_3__*) ; 
 int /*<<< orphan*/  OpcDoPld (TYPE_3__*) ; 
 int /*<<< orphan*/  OpcDoPrintf (TYPE_3__*) ; 
 int /*<<< orphan*/  OpcDoUnicode (TYPE_3__*) ; 
 int /*<<< orphan*/  OpcDoUuId (TYPE_3__*) ; 
 int /*<<< orphan*/  OpcSetOptimalIntegerSize (TYPE_3__*) ; 
#define  PARSEOP_ACCESSAS 139 
#define  PARSEOP_CONNECTION 138 
#define  PARSEOP_EISAID 137 
#define  PARSEOP_FPRINTF 136 
#define  PARSEOP_INCLUDE 135 
#define  PARSEOP_INTEGER 134 
#define  PARSEOP_OFFSET 133 
#define  PARSEOP_PRINTF 132 
#define  PARSEOP_TIMER 131 
#define  PARSEOP_TOPLD 130 
#define  PARSEOP_TOUUID 129 
#define  PARSEOP_UNICODE 128 
 int /*<<< orphan*/  TRUE ; 

void
OpcGenerateAmlOpcode (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT16                  Index;


    Index = (UINT16) (Op->Asl.ParseOpcode - ASL_PARSE_OPCODE_BASE);

    Op->Asl.AmlOpcode     = AslKeywordMapping[Index].AmlOpcode;
    Op->Asl.AcpiBtype     = AslKeywordMapping[Index].AcpiBtype;
    Op->Asl.CompileFlags |= AslKeywordMapping[Index].Flags;

    if (!Op->Asl.Value.Integer)
    {
        Op->Asl.Value.Integer = AslKeywordMapping[Index].Value;
    }

    /* Special handling for some opcodes */

    switch (Op->Asl.ParseOpcode)
    {
    case PARSEOP_INTEGER:
        /*
         * Set the opcode based on the size of the integer
         */
        (void) OpcSetOptimalIntegerSize (Op);
        break;

    case PARSEOP_OFFSET:

        Op->Asl.AmlOpcodeLength = 1;
        break;

    case PARSEOP_ACCESSAS:

        OpcDoAccessAs (Op);
        break;

    case PARSEOP_CONNECTION:

        OpcDoConnection (Op);
        break;

    case PARSEOP_EISAID:

        OpcDoEisaId (Op);
        break;

    case PARSEOP_PRINTF:

        OpcDoPrintf (Op);
        break;

    case PARSEOP_FPRINTF:

        OpcDoFprintf (Op);
        break;

    case PARSEOP_TOPLD:

        OpcDoPld (Op);
        break;

    case PARSEOP_TOUUID:

        OpcDoUuId (Op);
        break;

    case PARSEOP_UNICODE:

        OpcDoUnicode (Op);
        break;

    case PARSEOP_INCLUDE:

        AslGbl_HasIncludeFiles = TRUE;
        break;

    case PARSEOP_TIMER:

        if (AcpiGbl_IntegerBitWidth == 32)
        {
            AslError (ASL_REMARK, ASL_MSG_TRUNCATION, Op, NULL);
        }
        break;

    default:

        /* Nothing to do for other opcodes */

        break;
    }

    return;
}