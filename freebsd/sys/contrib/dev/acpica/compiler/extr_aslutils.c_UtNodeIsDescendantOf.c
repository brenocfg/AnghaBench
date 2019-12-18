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
struct TYPE_4__ {struct TYPE_4__* Parent; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_1__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
UtNodeIsDescendantOf (
    ACPI_NAMESPACE_NODE     *Node1,
    ACPI_NAMESPACE_NODE     *Node2)
{

    if (Node1 == Node2)
    {
        return (FALSE);
    }

    if (!Node2)
    {
        return (TRUE); /* All nodes descend from the root */
    }

    /* Walk upward until the root is reached or parent is found */

    while (Node1)
    {
        if (Node1 == Node2)
        {
            return (TRUE);
        }

        Node1 = Node1->Parent;
    }

    return (FALSE);
}