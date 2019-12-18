#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_8__ {int Flags; } ;
struct TYPE_6__ {int AmlOpcode; } ;
struct TYPE_7__ {TYPE_1__ Common; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;
typedef  TYPE_3__ ACPI_OPCODE_INFO ;

/* Variables and functions */
#define  AML_BANK_FIELD_OP 142 
#define  AML_BUFFER_OP 141 
#define  AML_DEVICE_OP 140 
#define  AML_ELSE_OP 139 
#define  AML_FIELD_OP 138 
 int AML_HAS_ARGS ; 
#define  AML_IF_OP 137 
#define  AML_INDEX_FIELD_OP 136 
#define  AML_METHOD_OP 135 
#define  AML_PACKAGE_OP 134 
#define  AML_POWER_RESOURCE_OP 133 
#define  AML_PROCESSOR_OP 132 
#define  AML_SCOPE_OP 131 
#define  AML_THERMAL_ZONE_OP 130 
#define  AML_VARIABLE_PACKAGE_OP 129 
#define  AML_WHILE_OP 128 
 TYPE_3__* AcpiPsGetOpcodeInfo (int) ; 
 int /*<<< orphan*/  BLOCK_COMMA_LIST ; 
 int /*<<< orphan*/  BLOCK_NONE ; 

UINT32
AcpiDmListType (
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
    case AML_METHOD_OP:
    case AML_DEVICE_OP:
    case AML_SCOPE_OP:
    case AML_POWER_RESOURCE_OP:
    case AML_PROCESSOR_OP:
    case AML_THERMAL_ZONE_OP:
    case AML_IF_OP:
    case AML_WHILE_OP:
    case AML_FIELD_OP:
    case AML_INDEX_FIELD_OP:
    case AML_BANK_FIELD_OP:

        return (BLOCK_NONE);

    case AML_BUFFER_OP:
    case AML_PACKAGE_OP:
    case AML_VARIABLE_PACKAGE_OP:

        return (BLOCK_COMMA_LIST);

    default:

        OpInfo = AcpiPsGetOpcodeInfo (Op->Common.AmlOpcode);
        if (OpInfo->Flags & AML_HAS_ARGS)
        {
            return (BLOCK_COMMA_LIST);
        }

        return (BLOCK_NONE);
    }
}