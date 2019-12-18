#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_3__ {char* Invocation; int /*<<< orphan*/  Description; scalar_t__ LineCount; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_1__ ACPI_DB_COMMAND_HELP ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiOsPrintf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ tolower (int) ; 

__attribute__((used)) static BOOLEAN
AcpiDbMatchCommandHelp (
    const char                  *Command,
    const ACPI_DB_COMMAND_HELP  *Help)
{
    char                    *Invocation = Help->Invocation;
    UINT32                  LineCount;


    /* Valid commands in the help table begin with a couple of spaces */

    if (*Invocation != ' ')
    {
        return (FALSE);
    }

    while (*Invocation == ' ')
    {
        Invocation++;
    }

    /* Match command name (full command or substring) */

    while ((*Command) && (*Invocation) && (*Invocation != ' '))
    {
        if (tolower ((int) *Command) != tolower ((int) *Invocation))
        {
            return (FALSE);
        }

        Invocation++;
        Command++;
    }

    /* Print the appropriate number of help lines */

    LineCount = Help->LineCount;
    while (LineCount)
    {
        AcpiOsPrintf ("%-38s : %s", Help->Invocation, Help->Description);
        Help++;
        LineCount--;
    }

    return (TRUE);
}