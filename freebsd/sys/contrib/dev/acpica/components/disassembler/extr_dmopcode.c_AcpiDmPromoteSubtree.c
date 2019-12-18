#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* Arg; } ;
struct TYPE_6__ {TYPE_3__* Next; TYPE_3__* Parent; TYPE_1__ Value; } ;
struct TYPE_7__ {TYPE_2__ Common; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */

__attribute__((used)) static void
AcpiDmPromoteSubtree (
    ACPI_PARSE_OBJECT       *StartOp)
{
    ACPI_PARSE_OBJECT       *Op;
    ACPI_PARSE_OBJECT       *ParentOp;


    /* New parent for subtree elements */

    ParentOp = StartOp->Common.Parent;

    /* First child starts the subtree */

    Op = StartOp->Common.Value.Arg;

    /* Walk the top-level elements of the subtree */

    while (Op)
    {
        Op->Common.Parent = ParentOp;
        if (!Op->Common.Next)
        {
            /* Last Op in list, update its next field */

            Op->Common.Next = StartOp->Common.Next;
            break;
        }
        Op = Op->Common.Next;
    }
}