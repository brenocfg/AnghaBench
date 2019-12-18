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
struct TYPE_4__ {struct TYPE_4__* Identifier; struct TYPE_4__* Replacement; struct TYPE_4__* Next; int /*<<< orphan*/  Persist; } ;
typedef  TYPE_1__ PR_DEFINE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (TYPE_1__*) ; 
 TYPE_1__* AslGbl_DefineList ; 

void
PrTerminatePreprocessor (
    void)
{
    PR_DEFINE_INFO          *DefineInfo;


    /*
     * The persistent defines (created on the command line) are always at the
     * end of the list. We save them.
     */
    while ((AslGbl_DefineList) && (!AslGbl_DefineList->Persist))
    {
        DefineInfo = AslGbl_DefineList;
        AslGbl_DefineList = DefineInfo->Next;

        ACPI_FREE (DefineInfo->Replacement);
        ACPI_FREE (DefineInfo->Identifier);
        ACPI_FREE (DefineInfo);
    }
}