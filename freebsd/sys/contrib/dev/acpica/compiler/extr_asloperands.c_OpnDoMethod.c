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
typedef  int UINT8 ;
struct TYPE_7__ {int Integer; } ;
struct TYPE_8__ {scalar_t__ ParseOpcode; int AmlLength; int Extra; int /*<<< orphan*/  AmlOpcode; TYPE_1__ Value; TYPE_3__* Next; TYPE_3__* Child; } ;
struct TYPE_9__ {TYPE_2__ Asl; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  AML_RAW_DATA_BYTE ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_SYNC_LEVEL ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OpcAmlConstantWalk (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ PARSEOP_DEFAULT_ARG ; 
 scalar_t__ PARSEOP_RAW_DATA ; 

__attribute__((used)) static void
OpnDoMethod (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *Next;

    /* Optional arguments for this opcode with defaults */

    UINT8                   NumArgs = 0;
    UINT8                   Serialized = 0;
    UINT8                   Concurrency = 0;
    UINT8                   MethodFlags;


    /* Opcode and package length first */
    /* Method name */

    Next = Op->Asl.Child;

    /* Num args */

    Next = Next->Asl.Next;
    if (Next->Asl.ParseOpcode != PARSEOP_DEFAULT_ARG)
    {
        NumArgs = (UINT8) Next->Asl.Value.Integer;
        Next->Asl.ParseOpcode = PARSEOP_DEFAULT_ARG;
    }

    /* Serialized Flag */

    Next = Next->Asl.Next;
    if (Next->Asl.ParseOpcode != PARSEOP_DEFAULT_ARG)
    {
        Serialized = (UINT8) Next->Asl.Value.Integer;
        Next->Asl.ParseOpcode = PARSEOP_DEFAULT_ARG;
    }

    /* Concurrency value (valid values are 0-15) */

    Next = Next->Asl.Next;
    if (Next->Asl.ParseOpcode != PARSEOP_DEFAULT_ARG)
    {
        /* This is a ByteConstExpr, so eval the constant now */

        OpcAmlConstantWalk (Next, 0, NULL);

        if (Next->Asl.Value.Integer > 15)
        {
            AslError (ASL_ERROR, ASL_MSG_SYNC_LEVEL, Next, NULL);
        }

        Concurrency = (UINT8) Next->Asl.Value.Integer;
    }

    /* Put the bits in their proper places */

    MethodFlags = (UINT8)
        ((NumArgs & 0x7) |
        ((Serialized & 0x1) << 3) |
        ((Concurrency & 0xF) << 4));

    /* Use the last node for the combined flags byte */

    Next->Asl.Value.Integer = MethodFlags;
    Next->Asl.AmlOpcode = AML_RAW_DATA_BYTE;
    Next->Asl.AmlLength = 1;
    Next->Asl.ParseOpcode = PARSEOP_RAW_DATA;

    /* Save the arg count in the first node */

    Op->Asl.Extra = NumArgs;
}