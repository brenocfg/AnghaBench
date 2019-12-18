#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_11__ {scalar_t__ Integer; } ;
struct TYPE_12__ {scalar_t__ AmlOpcode; scalar_t__ ParseOpcode; int /*<<< orphan*/ * Node; TYPE_4__ Value; TYPE_3__* Child; TYPE_6__* Next; } ;
struct TYPE_13__ {TYPE_5__ Asl; } ;
struct TYPE_8__ {scalar_t__ Integer; } ;
struct TYPE_9__ {TYPE_1__ Value; } ;
struct TYPE_10__ {TYPE_2__ Asl; } ;
typedef  TYPE_6__ ACPI_PARSE_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 scalar_t__ AML_INT_CONNECTION_OP ; 
 scalar_t__ AML_INT_NAMEDFIELD_OP ; 
 char* AcpiNsGetExternalPathname (int /*<<< orphan*/ *) ; 
 scalar_t__ PARSEOP_CONNECTION ; 
 scalar_t__ PARSEOP_NAMESEG ; 

char *
MpGetConnectionInfo (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  PinIndex,
    ACPI_NAMESPACE_NODE     **TargetNode,
    char                    **TargetName)
{
    ACPI_PARSE_OBJECT       *NextOp;
    UINT32                  i;


    /*
     * Handle Connection() here. Find the next named FieldUnit.
     * Note: we look at the ParseOpcode for the compiler, look
     * at the AmlOpcode for the disassembler.
     */
    if ((Op->Asl.AmlOpcode == AML_INT_CONNECTION_OP) ||
        (Op->Asl.ParseOpcode == PARSEOP_CONNECTION))
    {
        /* Find the correct field unit definition */

        NextOp = Op;
        for (i = 0; i <= PinIndex;)
        {
            NextOp = NextOp->Asl.Next;
            while (NextOp &&
                (NextOp->Asl.ParseOpcode != PARSEOP_NAMESEG) &&
                (NextOp->Asl.AmlOpcode != AML_INT_NAMEDFIELD_OP))
            {
                NextOp = NextOp->Asl.Next;
            }

            if (!NextOp)
            {
                return ("UNKNOWN");
            }

            /* Add length of this field to the current pin index */

            if (NextOp->Asl.ParseOpcode == PARSEOP_NAMESEG)
            {
                i += (UINT32) NextOp->Asl.Child->Asl.Value.Integer;
            }
            else /* AML_INT_NAMEDFIELD_OP */
            {
                i += (UINT32) NextOp->Asl.Value.Integer;
            }
        }

        /* Return the node and pathname for the field unit */

        *TargetNode = NextOp->Asl.Node;
        *TargetName = AcpiNsGetExternalPathname (*TargetNode);
        return ("-Field-");
    }

    return (NULL);
}