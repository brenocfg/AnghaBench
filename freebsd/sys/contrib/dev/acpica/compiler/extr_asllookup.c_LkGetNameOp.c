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
struct TYPE_9__ {int Flags; } ;
struct TYPE_7__ {scalar_t__ AmlOpcode; int CompileFlags; TYPE_2__* Next; TYPE_2__* Child; } ;
struct TYPE_8__ {TYPE_1__ Asl; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;
typedef  TYPE_3__ ACPI_OPCODE_INFO ;

/* Variables and functions */
 scalar_t__ AML_ALIAS_OP ; 
 int AML_CREATE ; 
 int AML_NAMED ; 
 TYPE_3__* AcpiPsGetOpcodeInfo (scalar_t__) ; 
 int OP_IS_NAME_DECLARATION ; 

__attribute__((used)) static ACPI_PARSE_OBJECT *
LkGetNameOp (
    ACPI_PARSE_OBJECT       *Op)
{
    const ACPI_OPCODE_INFO  *OpInfo;
    ACPI_PARSE_OBJECT       *NameOp = Op;


    OpInfo = AcpiPsGetOpcodeInfo (Op->Asl.AmlOpcode);


    /* Get the NamePath from the appropriate place */

    if (OpInfo->Flags & AML_NAMED)
    {
        /* For nearly all NAMED operators, the name reference is the first child */

        NameOp = Op->Asl.Child;
        if (Op->Asl.AmlOpcode == AML_ALIAS_OP)
        {
            /*
             * ALIAS is the only oddball opcode, the name declaration
             * (alias name) is the second operand
             */
            NameOp = Op->Asl.Child->Asl.Next;
        }
    }
    else if (OpInfo->Flags & AML_CREATE)
    {
        /* Name must appear as the last parameter */

        NameOp = Op->Asl.Child;
        while (!(NameOp->Asl.CompileFlags & OP_IS_NAME_DECLARATION))
        {
            NameOp = NameOp->Asl.Next;
        }
    }

    return (NameOp);
}