#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_10__ {scalar_t__ Class; } ;
struct TYPE_7__ {TYPE_3__* Arg; } ;
struct TYPE_8__ {scalar_t__ AmlOpcode; TYPE_3__* Next; TYPE_1__ Value; } ;
struct TYPE_9__ {TYPE_2__ Common; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;
typedef  TYPE_4__ ACPI_OPCODE_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_METHOD_NUM_ARGS ; 
 scalar_t__ AML_CLASS_CONTROL ; 
 scalar_t__ AML_CLASS_CREATE ; 
 scalar_t__ AML_CLASS_EXECUTE ; 
 scalar_t__ AML_CLASS_NAMED_OBJECT ; 
 scalar_t__ AML_INT_NAMEPATH_OP ; 
 scalar_t__ AML_NOTIFY_OP ; 
 scalar_t__ AML_REF_OF_OP ; 
 scalar_t__ AML_STORE_OP ; 
 TYPE_4__* AcpiPsGetOpcodeInfo (scalar_t__) ; 

__attribute__((used)) static UINT32
AcpiDmInspectPossibleArgs (
    UINT32                  CurrentOpArgCount,
    UINT32                  TargetCount,
    ACPI_PARSE_OBJECT       *Op)
{
    const ACPI_OPCODE_INFO  *OpInfo;
    UINT32                  i;
    UINT32                  ArgumentCount = 0;
    ACPI_PARSE_OBJECT       *NextOp;
    ACPI_PARSE_OBJECT       *ExecuteOp;


    if (!Op)
    {
        return (0);
    }

    /* Lookahead for the maximum number of possible arguments */

    NextOp = Op->Common.Next;

    for (i = 0; (i < ACPI_METHOD_NUM_ARGS) && NextOp; i++)
    {
        OpInfo = AcpiPsGetOpcodeInfo (NextOp->Common.AmlOpcode);

        /* Any one of these operators is "very probably" not a method arg */

        if ((NextOp->Common.AmlOpcode == AML_STORE_OP) ||
            (NextOp->Common.AmlOpcode == AML_NOTIFY_OP) ||
            (OpInfo->Class == AML_CLASS_CONTROL) ||
            (OpInfo->Class == AML_CLASS_CREATE) ||
            (OpInfo->Class == AML_CLASS_NAMED_OBJECT))
        {
            break;
        }

        if (OpInfo->Class == AML_CLASS_EXECUTE)
        {
            /* Probable that this is method arg if there is no target */

            ExecuteOp = NextOp->Common.Value.Arg;
            while (ExecuteOp)
            {
                if ((ExecuteOp->Common.AmlOpcode == AML_INT_NAMEPATH_OP) &&
                    (ExecuteOp->Common.Value.Arg == NULL))
                {
                    /* No target, could be a method arg */

                    break;
                }

                if (NextOp->Common.AmlOpcode == AML_REF_OF_OP)
                {
                    break;
                }

                ExecuteOp = ExecuteOp->Common.Next;
            }

            if (!ExecuteOp)
            {
                /* Has a target, not method arg */

                return (ArgumentCount);
            }
        }

        ArgumentCount++;
        NextOp = NextOp->Common.Next;
    }

    return (ArgumentCount);
}