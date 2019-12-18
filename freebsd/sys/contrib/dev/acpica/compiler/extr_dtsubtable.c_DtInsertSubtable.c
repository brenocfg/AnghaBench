#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* Peer; struct TYPE_4__* Child; scalar_t__ Depth; struct TYPE_4__* Parent; } ;
typedef  TYPE_1__ DT_SUBTABLE ;

/* Variables and functions */

void
DtInsertSubtable (
    DT_SUBTABLE             *ParentTable,
    DT_SUBTABLE             *Subtable)
{
    DT_SUBTABLE             *ChildTable;


    Subtable->Peer = NULL;
    Subtable->Parent = ParentTable;
    Subtable->Depth = ParentTable->Depth + 1;

    /* Link the new entry into the child list */

    if (!ParentTable->Child)
    {
        ParentTable->Child = Subtable;
    }
    else
    {
        /* Walk to the end of the child list */

        ChildTable = ParentTable->Child;
        while (ChildTable->Peer)
        {
            ChildTable = ChildTable->Peer;
        }

        /* Add new subtable at the end of the child list */

        ChildTable->Peer = Subtable;
    }
}