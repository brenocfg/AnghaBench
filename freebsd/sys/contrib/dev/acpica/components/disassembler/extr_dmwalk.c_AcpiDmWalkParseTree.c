#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ Level; } ;
struct TYPE_10__ {TYPE_2__* Parent; TYPE_2__* Next; } ;
struct TYPE_11__ {TYPE_1__ Common; } ;
typedef  scalar_t__ BOOLEAN ;
typedef  scalar_t__ (* ASL_WALK_CALLBACK ) (TYPE_2__*,scalar_t__,void*) ;
typedef  scalar_t__ ACPI_STATUS ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;
typedef  TYPE_4__ ACPI_OP_WALK_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 scalar_t__ ACPI_SUCCESS (scalar_t__) ; 
 scalar_t__ AE_CTRL_DEPTH ; 
 TYPE_2__* AcpiPsGetArg (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 

void
AcpiDmWalkParseTree (
    ACPI_PARSE_OBJECT       *Op,
    ASL_WALK_CALLBACK       DescendingCallback,
    ASL_WALK_CALLBACK       AscendingCallback,
    void                    *Context)
{
    BOOLEAN                 NodePreviouslyVisited;
    ACPI_PARSE_OBJECT       *StartOp = Op;
    ACPI_STATUS             Status;
    ACPI_PARSE_OBJECT       *Next;
    ACPI_OP_WALK_INFO       *Info = Context;


    Info->Level = 0;
    NodePreviouslyVisited = FALSE;

    while (Op)
    {
        if (NodePreviouslyVisited)
        {
            if (AscendingCallback)
            {
                Status = AscendingCallback (Op, Info->Level, Context);
                if (ACPI_FAILURE (Status))
                {
                    return;
                }
            }
        }
        else
        {
            /* Let the callback process the node */

            Status = DescendingCallback (Op, Info->Level, Context);
            if (ACPI_SUCCESS (Status))
            {
                /* Visit children first, once */

                Next = AcpiPsGetArg (Op, 0);
                if (Next)
                {
                    Info->Level++;
                    Op = Next;
                    continue;
                }
            }
            else if (Status != AE_CTRL_DEPTH)
            {
                /* Exit immediately on any error */

                return;
            }
        }

        /* Terminate walk at start op */

        if (Op == StartOp)
        {
            break;
        }

        /* No more children, re-visit this node */

        if (!NodePreviouslyVisited)
        {
            NodePreviouslyVisited = TRUE;
            continue;
        }

        /* No more children, visit peers */

        if (Op->Common.Next)
        {
            Op = Op->Common.Next;
            NodePreviouslyVisited = FALSE;
        }
        else
        {
            /* No peers, re-visit parent */

            if (Info->Level != 0 )
            {
                Info->Level--;
            }

            Op = Op->Common.Parent;
            NodePreviouslyVisited = TRUE;
        }
    }

    /* If we get here, the walk completed with no errors */

    return;
}