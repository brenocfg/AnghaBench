#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* Peer; struct TYPE_5__* Child; } ;
typedef  TYPE_1__ DT_SUBTABLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 

DT_SUBTABLE *
DtGetNextSubtable (
    DT_SUBTABLE             *ParentTable,
    DT_SUBTABLE             *ChildTable)
{
    ACPI_FUNCTION_ENTRY ();


    if (!ChildTable)
    {
        /* It's really the parent's _scope_ that we want */

        return (ParentTable->Child);
    }

    /* Otherwise just return the next peer (NULL if at end-of-list) */

    return (ChildTable->Peer);
}