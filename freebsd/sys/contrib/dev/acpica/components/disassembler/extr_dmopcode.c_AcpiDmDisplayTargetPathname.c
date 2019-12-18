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
struct TYPE_12__ {int Flags; } ;
struct TYPE_9__ {char* String; TYPE_4__* Arg; } ;
struct TYPE_10__ {scalar_t__ AmlOpcode; int /*<<< orphan*/  Node; TYPE_2__ Value; TYPE_4__* Next; } ;
struct TYPE_8__ {scalar_t__ AmlOpcode; } ;
struct TYPE_11__ {TYPE_3__ Asl; TYPE_1__ Common; } ;
typedef  TYPE_4__ ACPI_PARSE_OBJECT ;
typedef  TYPE_5__ ACPI_OPCODE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 int AML_HAS_TARGET ; 
 scalar_t__ AML_INT_NAMEPATH_OP ; 
 scalar_t__ AML_RETURN_OP ; 
 char* AcpiNsGetExternalPathname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 TYPE_5__* AcpiPsGetOpcodeInfo (scalar_t__) ; 

void
AcpiDmDisplayTargetPathname (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *NextOp;
    ACPI_PARSE_OBJECT       *PrevOp = NULL;
    char                    *Pathname;
    const ACPI_OPCODE_INFO  *OpInfo;


    if (Op->Common.AmlOpcode == AML_RETURN_OP)
    {
        PrevOp = Op->Asl.Value.Arg;
    }
    else
    {
        OpInfo = AcpiPsGetOpcodeInfo (Op->Common.AmlOpcode);
        if (!(OpInfo->Flags & AML_HAS_TARGET))
        {
            return;
        }

        /* Target is the last Op in the arg list */

        NextOp = Op->Asl.Value.Arg;
        while (NextOp)
        {
            PrevOp = NextOp;
            NextOp = PrevOp->Asl.Next;
        }
    }

    if (!PrevOp)
    {
        return;
    }

    /* We must have a namepath AML opcode */

    if (PrevOp->Asl.AmlOpcode != AML_INT_NAMEPATH_OP)
    {
        return;
    }

    /* A null string is the "no target specified" case */

    if (!PrevOp->Asl.Value.String)
    {
        return;
    }

    /* No node means "unresolved external reference" */

    if (!PrevOp->Asl.Node)
    {
        AcpiOsPrintf (" /* External reference */");
        return;
    }

    /* Ignore if path is already from the root */

    if (*PrevOp->Asl.Value.String == '\\')
    {
        return;
    }

    /* Now: we can get the full pathname */

    Pathname = AcpiNsGetExternalPathname (PrevOp->Asl.Node);
    if (!Pathname)
    {
        return;
    }

    AcpiOsPrintf (" /* %s */", Pathname);
    ACPI_FREE (Pathname);
}