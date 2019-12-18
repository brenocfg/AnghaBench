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
struct TYPE_4__ {char* Filename; struct TYPE_4__* Next; scalar_t__ LineNumber; } ;
typedef  TYPE_1__ ASL_LISTING_NODE ;

/* Variables and functions */
 TYPE_1__* AslGbl_ListingNode ; 
 TYPE_1__* UtLocalCalloc (int) ; 

void
LsPushNode (
    char                    *Filename)
{
    ASL_LISTING_NODE        *Lnode;


    /* Create a new node */

    Lnode = UtLocalCalloc (sizeof (ASL_LISTING_NODE));

    /* Initialize */

    Lnode->Filename = Filename;
    Lnode->LineNumber = 0;

    /* Link (push) */

    Lnode->Next = AslGbl_ListingNode;
    AslGbl_ListingNode = Lnode;
}