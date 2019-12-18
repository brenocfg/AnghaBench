#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_9__ {int /*<<< orphan*/  ParseOpName; scalar_t__ Child; } ;
struct TYPE_8__ {scalar_t__ Arg; } ;
struct TYPE_10__ {TYPE_1__ Value; int /*<<< orphan*/  AmlOpcode; } ;
struct TYPE_12__ {TYPE_2__ Asl; TYPE_3__ Common; } ;
struct TYPE_11__ {int /*<<< orphan*/  OpInfo; int /*<<< orphan*/  Opcode; TYPE_5__* Op; } ;
typedef  TYPE_4__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_5__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASL_PARSE_OUTPUT ; 
 int /*<<< orphan*/  AcpiDsExecEndOp (TYPE_4__*) ; 
 int /*<<< orphan*/  AcpiFormatException (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiPsGetOpcodeInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
OpcAmlEvaluationWalk2 (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{
    ACPI_WALK_STATE         *WalkState = Context;
    ACPI_STATUS             Status;


    WalkState->Op = Op;
    WalkState->Opcode = Op->Common.AmlOpcode;
    WalkState->OpInfo = AcpiPsGetOpcodeInfo (Op->Common.AmlOpcode);

    /* Copy child pointer to Arg for compatibility with Interpreter */

    if (Op->Asl.Child)
    {
        Op->Common.Value.Arg = Op->Asl.Child;
    }

    /* Call AML dispatcher */

    Status = AcpiDsExecEndOp (WalkState);
    if (ACPI_FAILURE (Status))
    {
        DbgPrint (ASL_PARSE_OUTPUT,
            "%s: Constant interpretation failed (2) - %s\n",
            Op->Asl.ParseOpName, AcpiFormatException (Status));
    }

    return (Status);
}