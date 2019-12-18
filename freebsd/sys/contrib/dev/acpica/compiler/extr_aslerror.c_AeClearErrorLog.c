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
struct TYPE_4__ {struct TYPE_4__* Next; } ;
typedef  TYPE_1__ ASL_ERROR_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (TYPE_1__*) ; 
 TYPE_1__* AslGbl_ErrorLog ; 

void
AeClearErrorLog (
    void)
{
    ASL_ERROR_MSG           *Enode = AslGbl_ErrorLog;
    ASL_ERROR_MSG           *Next;


    /* Walk the error node list */

    while (Enode)
    {
        Next = Enode->Next;
        ACPI_FREE (Enode);
        Enode = Next;
    }

   AslGbl_ErrorLog = NULL;
}