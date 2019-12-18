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
struct TYPE_5__ {struct TYPE_5__* Next; } ;
typedef  TYPE_1__ ASL_LISTING_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_COMPILER_INTERNAL ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* AslGbl_ListingNode ; 

ASL_LISTING_NODE *
LsPopNode (
    void)
{
    ASL_LISTING_NODE        *Lnode;


    /* Just grab the node at the head of the list */

    Lnode = AslGbl_ListingNode;
    if ((!Lnode) ||
        (!Lnode->Next))
    {
        AslError (ASL_ERROR, ASL_MSG_COMPILER_INTERNAL, NULL,
            "Could not pop empty listing stack");
        return (AslGbl_ListingNode);
    }

    AslGbl_ListingNode = Lnode->Next;
    ACPI_FREE (Lnode);

    /* New "Current" node is the new head */

    return (AslGbl_ListingNode);
}