#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct TYPE_11__* Peer; scalar_t__ Child; } ;
typedef  int /*<<< orphan*/  (* DT_WALK_CALLBACK ) (TYPE_1__*,void*,void*) ;
typedef  TYPE_1__ DT_SUBTABLE ;

/* Variables and functions */
 TYPE_1__* AslGbl_RootTable ; 
 TYPE_1__* DtGetNextSubtable (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* DtGetParentSubtable (TYPE_1__*) ; 

void
DtWalkTableTree (
    DT_SUBTABLE             *StartTable,
    DT_WALK_CALLBACK        UserFunction,
    void                    *Context,
    void                    *ReturnValue)
{
    DT_SUBTABLE             *ParentTable;
    DT_SUBTABLE             *ChildTable;


    ParentTable = StartTable;
    ChildTable = NULL;

    if (!ParentTable)
    {
        return;
    }

    UserFunction (ParentTable, Context, ReturnValue);

    while (1)
    {
        ChildTable = DtGetNextSubtable (ParentTable, ChildTable);
        if (ChildTable)
        {
            UserFunction (ChildTable, Context, ReturnValue);

            if (ChildTable->Child)
            {
                ParentTable = ChildTable;
                ChildTable = NULL;
            }
        }
        else
        {
            ChildTable = ParentTable;
            if (ChildTable == AslGbl_RootTable)
            {
                break;
            }

            ParentTable = DtGetParentSubtable (ParentTable);

            if (ChildTable->Peer == StartTable)
            {
                break;
            }
        }
    }
}