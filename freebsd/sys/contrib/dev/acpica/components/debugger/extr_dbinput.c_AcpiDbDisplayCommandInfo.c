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
struct TYPE_4__ {scalar_t__ Invocation; } ;
typedef  scalar_t__ BOOLEAN ;
typedef  TYPE_1__ ACPI_DB_COMMAND_HELP ;

/* Variables and functions */
 scalar_t__ AcpiDbMatchCommandHelp (char const*,TYPE_1__ const*) ; 
 TYPE_1__* AcpiGbl_DbCommandHelp ; 

__attribute__((used)) static void
AcpiDbDisplayCommandInfo (
    const char              *Command,
    BOOLEAN                 DisplayAll)
{
    const ACPI_DB_COMMAND_HELP  *Next;
    BOOLEAN                     Matched;


    Next = AcpiGbl_DbCommandHelp;
    while (Next->Invocation)
    {
        Matched = AcpiDbMatchCommandHelp (Command, Next);
        if (!DisplayAll && Matched)
        {
            return;
        }

        Next++;
    }
}