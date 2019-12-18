#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_8__ {scalar_t__ Integer; } ;
struct TYPE_9__ {scalar_t__ ParseOpcode; int CompileFlags; TYPE_1__ Value; } ;
struct TYPE_10__ {TYPE_2__ Asl; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_ERROR ; 
 TYPE_3__* ASL_GET_PEER_NODE (TYPE_3__*) ; 
 int /*<<< orphan*/  ASL_MSG_DUPLICATE_ITEM ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int OP_IS_DUPLICATE ; 
 scalar_t__ PARSEOP_DEFAULT_ARG ; 

void
RsCheckListForDuplicates (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *NextValueOp = Op;
    ACPI_PARSE_OBJECT       *NextOp;
    UINT32                  Value;


    if (!Op)
    {
        return;
    }

    /* Search list once for each value in the list */

    while (NextValueOp)
    {
        Value = (UINT32) NextValueOp->Asl.Value.Integer;

        /* Compare this value to all remaining values in the list */

        NextOp = ASL_GET_PEER_NODE (NextValueOp);
        while (NextOp)
        {
            if (NextOp->Asl.ParseOpcode != PARSEOP_DEFAULT_ARG)
            {
                /* Compare values */

                if (Value == (UINT32) NextOp->Asl.Value.Integer)
                {
                    /* Emit error only once per duplicate node */

                    if (!(NextOp->Asl.CompileFlags & OP_IS_DUPLICATE))
                    {
                        NextOp->Asl.CompileFlags |= OP_IS_DUPLICATE;
                        AslError (ASL_ERROR, ASL_MSG_DUPLICATE_ITEM,
                            NextOp, NULL);
                    }
                }
            }

            NextOp = ASL_GET_PEER_NODE (NextOp);
        }

        NextValueOp = ASL_GET_PEER_NODE (NextValueOp);
    }
}