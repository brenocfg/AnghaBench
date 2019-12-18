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
struct TYPE_4__ {scalar_t__ LogicalLineNumber; struct TYPE_4__* Next; } ;
typedef  TYPE_1__ ASL_ERROR_MSG ;

/* Variables and functions */
 TYPE_1__* AslGbl_ErrorLog ; 

__attribute__((used)) static void
AeAddToErrorLog (
    ASL_ERROR_MSG           *Enode)
{
    ASL_ERROR_MSG           *Next;
    ASL_ERROR_MSG           *Prev;


    /* If Gbl_ErrorLog is null, this is the first error node */

    if (!AslGbl_ErrorLog)
    {
        AslGbl_ErrorLog = Enode;
        return;
    }

    /*
     * Walk error list until we find a line number greater than ours.
     * List is sorted according to line number.
     */
    Prev = NULL;
    Next = AslGbl_ErrorLog;

    while ((Next) && (Next->LogicalLineNumber <= Enode->LogicalLineNumber))
    {
        Prev = Next;
        Next = Next->Next;
    }

    /* Found our place in the list */

    Enode->Next = Next;

    if (Prev)
    {
        Prev->Next = Enode;
    }
    else
    {
        AslGbl_ErrorLog = Enode;
    }
}