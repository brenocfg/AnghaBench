#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ACPI_SIZE ;

/* Variables and functions */
 int ACPI_PTR_DIFF (char*,char*) ; 
 char* UtLocalCacheCalloc (int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static char *
DtTrim (
    char                    *String)
{
    char                    *Start;
    char                    *End;
    char                    *ReturnString;
    ACPI_SIZE               Length;


    /* Skip lines that start with a space */

    if (*String == 0 || !strcmp (String, " "))
    {
        ReturnString = UtLocalCacheCalloc (1);
        return (ReturnString);
    }

    /* Setup pointers to start and end of input string */

    Start = String;
    End = String + strlen (String) - 1;

    /* Find first non-whitespace character */

    while ((Start <= End) && ((*Start == ' ') || (*Start == '\t')))
    {
        Start++;
    }

    /* Find last non-space character */

    while (End >= Start)
    {
        if (*End == '\n')
        {
            End--;
            continue;
        }

        if (*End != ' ')
        {
            break;
        }

        End--;
    }

    /* Remove any quotes around the string */

    if (*Start == '\"')
    {
        Start++;
    }
    if (*End == '\"')
    {
        End--;
    }

    /* Create the trimmed return string */

    Length = ACPI_PTR_DIFF (End, Start) + 1;
    ReturnString = UtLocalCacheCalloc (Length + 1);
    if (strlen (Start))
    {
        strncpy (ReturnString, Start, Length);
    }

    ReturnString[Length] = 0;
    return (ReturnString);
}