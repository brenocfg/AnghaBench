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
typedef  int UINT32 ;
struct TYPE_12__ {int Flags; } ;
struct TYPE_10__ {int AmlOpcode; TYPE_2__* Parent; int /*<<< orphan*/  DisasmOpcode; } ;
struct TYPE_11__ {TYPE_3__ Common; } ;
struct TYPE_8__ {int const AmlOpcode; } ;
struct TYPE_9__ {TYPE_1__ Common; } ;
typedef  TYPE_4__ ACPI_PARSE_OBJECT ;
typedef  TYPE_5__ ACPI_OPCODE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DASM_PLD_METHOD ; 
 int /*<<< orphan*/  ACPI_DASM_UNICODE ; 
 int /*<<< orphan*/  ACPI_DASM_UUID ; 
#define  AML_BANK_FIELD_OP 144 
#define  AML_BUFFER_OP 143 
#define  AML_DEVICE_OP 142 
#define  AML_ELSE_OP 141 
#define  AML_EVENT_OP 140 
#define  AML_FIELD_OP 139 
 int AML_HAS_ARGS ; 
#define  AML_IF_OP 138 
#define  AML_INDEX_FIELD_OP 137 
#define  AML_INT_METHODCALL_OP 136 
#define  AML_METHOD_OP 135 
#define  AML_PACKAGE_OP 134 
#define  AML_POWER_RESOURCE_OP 133 
#define  AML_PROCESSOR_OP 132 
#define  AML_SCOPE_OP 131 
#define  AML_THERMAL_ZONE_OP 130 
#define  AML_VARIABLE_PACKAGE_OP 129 
#define  AML_WHILE_OP 128 
 TYPE_5__* AcpiPsGetOpcodeInfo (int) ; 
 int BLOCK_BRACE ; 
 int BLOCK_NONE ; 
 int BLOCK_PAREN ; 

UINT32
AcpiDmBlockType (
    ACPI_PARSE_OBJECT       *Op)
{
    const ACPI_OPCODE_INFO  *OpInfo;


    if (!Op)
    {
        return (BLOCK_NONE);
    }

    switch (Op->Common.AmlOpcode)
    {
    case AML_ELSE_OP:

        return (BLOCK_BRACE);

    case AML_METHOD_OP:
    case AML_DEVICE_OP:
    case AML_SCOPE_OP:
    case AML_PROCESSOR_OP:
    case AML_POWER_RESOURCE_OP:
    case AML_THERMAL_ZONE_OP:
    case AML_IF_OP:
    case AML_WHILE_OP:
    case AML_FIELD_OP:
    case AML_INDEX_FIELD_OP:
    case AML_BANK_FIELD_OP:

        return (BLOCK_PAREN | BLOCK_BRACE);

    case AML_BUFFER_OP:

        if ((Op->Common.DisasmOpcode == ACPI_DASM_UNICODE) ||
            (Op->Common.DisasmOpcode == ACPI_DASM_UUID) ||
            (Op->Common.DisasmOpcode == ACPI_DASM_PLD_METHOD))
        {
            return (BLOCK_NONE);
        }

        /*lint -fallthrough */

    case AML_PACKAGE_OP:
    case AML_VARIABLE_PACKAGE_OP:

        return (BLOCK_PAREN | BLOCK_BRACE);

    case AML_EVENT_OP:

        return (BLOCK_PAREN);

    case AML_INT_METHODCALL_OP:

        if (Op->Common.Parent &&
            ((Op->Common.Parent->Common.AmlOpcode == AML_PACKAGE_OP) ||
             (Op->Common.Parent->Common.AmlOpcode == AML_VARIABLE_PACKAGE_OP)))
        {
            /* This is a reference to a method, not an invocation */

            return (BLOCK_NONE);
        }

        /*lint -fallthrough */

    default:

        OpInfo = AcpiPsGetOpcodeInfo (Op->Common.AmlOpcode);
        if (OpInfo->Flags & AML_HAS_ARGS)
        {
            return (BLOCK_PAREN);
        }

        return (BLOCK_NONE);
    }
}