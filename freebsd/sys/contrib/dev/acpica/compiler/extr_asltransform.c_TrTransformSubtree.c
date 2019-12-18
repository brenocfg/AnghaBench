#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* String; int Integer; } ;
struct TYPE_11__ {scalar_t__ AmlOpcode; int ParseOpcode; int /*<<< orphan*/ * ExternalName; TYPE_1__ Value; TYPE_3__* Child; TYPE_3__* Parent; } ;
struct TYPE_12__ {TYPE_2__ Asl; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 scalar_t__ AML_RAW_DATA_BYTE ; 
 int /*<<< orphan*/  ASL_MSG_LEGACY_PROCESSOR_OP ; 
 int /*<<< orphan*/  ASL_MSG_LONG_SLEEP ; 
 int /*<<< orphan*/  ASL_MSG_UNLOAD ; 
 int /*<<< orphan*/  ASL_REMARK ; 
 int /*<<< orphan*/  ASL_WARNING ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AslGbl_TempCount ; 
 int /*<<< orphan*/  ExDoExternal (TYPE_3__*) ; 
#define  PARSEOP_DEFINITION_BLOCK 135 
#define  PARSEOP_EXTERNAL 134 
#define  PARSEOP_METHOD 133 
#define  PARSEOP_PROCESSOR 132 
#define  PARSEOP_SLEEP 131 
 int PARSEOP_STRING_LITERAL ; 
#define  PARSEOP_SWITCH 130 
#define  PARSEOP_UNLOAD 129 
#define  PARSEOP___METHOD__ 128 
 int /*<<< orphan*/  TrDoDefinitionBlock (TYPE_3__*) ; 
 int /*<<< orphan*/  TrDoSwitch (TYPE_3__*) ; 
 int /*<<< orphan*/  UtSetParseOpName (TYPE_3__*) ; 

__attribute__((used)) static void
TrTransformSubtree (
    ACPI_PARSE_OBJECT           *Op)
{
    ACPI_PARSE_OBJECT           *MethodOp;


    if (Op->Asl.AmlOpcode == AML_RAW_DATA_BYTE)
    {
        return;
    }

    switch (Op->Asl.ParseOpcode)
    {
    case PARSEOP_DEFINITION_BLOCK:

        TrDoDefinitionBlock (Op);
        break;

    case PARSEOP_SWITCH:

        TrDoSwitch (Op);
        break;

    case PARSEOP_METHOD:
        /*
         * TBD: Zero the tempname (_T_x) count. Probably shouldn't be a global,
         * however
         */
        AslGbl_TempCount = 0;
        break;

    case PARSEOP_EXTERNAL:

        ExDoExternal (Op);
        break;

    case PARSEOP___METHOD__:

        /* Transform to a string op containing the parent method name */

        Op->Asl.ParseOpcode = PARSEOP_STRING_LITERAL;
        UtSetParseOpName (Op);

        /* Find the parent control method op */

        MethodOp = Op;
        while (MethodOp)
        {
            if (MethodOp->Asl.ParseOpcode == PARSEOP_METHOD)
            {
                /* First child contains the method name */

                MethodOp = MethodOp->Asl.Child;
                Op->Asl.Value.String = MethodOp->Asl.Value.String;
                return;
            }

            MethodOp = MethodOp->Asl.Parent;
        }

        /* At the root, invocation not within a control method */

        Op->Asl.Value.String = "\\";
        break;

    case PARSEOP_UNLOAD:

        AslError (ASL_WARNING, ASL_MSG_UNLOAD, Op, NULL);
        break;

    case PARSEOP_SLEEP:

        /* Remark for very long sleep values */

        if (Op->Asl.Child->Asl.Value.Integer > 1000)
        {
            AslError (ASL_REMARK, ASL_MSG_LONG_SLEEP, Op, NULL);
        }
        break;

    case PARSEOP_PROCESSOR:

        AslError (ASL_WARNING, ASL_MSG_LEGACY_PROCESSOR_OP, Op, Op->Asl.ExternalName);

        break;

    default:

        /* Nothing to do here for other opcodes */

        break;
    }
}