#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int AmlOpcode; int AmlOpcodeLength; int CompileFlags; int AmlLength; int /*<<< orphan*/  AmlSubtreeLength; scalar_t__ AmlPkgLenBytes; } ;
struct TYPE_6__ {TYPE_1__ Asl; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
#define  AML_BYTE_OP 131 
#define  AML_DWORD_OP 130 
#define  AML_QWORD_OP 129 
#define  AML_WORD_OP 128 
 scalar_t__ CgGetPackageLenByteCount (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int OP_AML_PACKAGE ; 

__attribute__((used)) static void
CgGenerateAmlOpcodeLength (
    ACPI_PARSE_OBJECT       *Op)
{

    /* Check for two-byte opcode */

    if (Op->Asl.AmlOpcode > 0x00FF)
    {
        Op->Asl.AmlOpcodeLength = 2;
    }
    else
    {
        Op->Asl.AmlOpcodeLength = 1;
    }

    /* Does this opcode have an associated "PackageLength" field? */

    Op->Asl.AmlPkgLenBytes = 0;
    if (Op->Asl.CompileFlags & OP_AML_PACKAGE)
    {
        Op->Asl.AmlPkgLenBytes = CgGetPackageLenByteCount (
            Op, Op->Asl.AmlSubtreeLength);
    }

    /* Data opcode lengths are easy */

    switch (Op->Asl.AmlOpcode)
    {
    case AML_BYTE_OP:

        Op->Asl.AmlLength = 1;
        break;

    case AML_WORD_OP:

        Op->Asl.AmlLength = 2;
        break;

    case AML_DWORD_OP:

        Op->Asl.AmlLength = 4;
        break;

    case AML_QWORD_OP:

        Op->Asl.AmlLength = 8;
        break;

    default:

        /* All data opcodes must be above */
        break;
    }
}