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
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_4__ {struct TYPE_4__* Next; } ;
typedef  TYPE_1__ ASL_ERROR_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  AePrintException (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* AslGbl_ErrorLog ; 

void
AePrintErrorLog (
    UINT32                  FileId)
{
    ASL_ERROR_MSG           *Enode = AslGbl_ErrorLog;


    /* Walk the error node list */

    while (Enode)
    {
        AePrintException (FileId, Enode, NULL);
        Enode = Enode->Next;
    }
}