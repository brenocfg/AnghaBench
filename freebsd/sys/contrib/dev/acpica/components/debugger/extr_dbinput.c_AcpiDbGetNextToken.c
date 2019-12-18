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
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TYPE_BUFFER ; 
 int /*<<< orphan*/  ACPI_TYPE_FIELD_UNIT ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  ACPI_TYPE_STRING ; 

char *
AcpiDbGetNextToken (
    char                    *String,
    char                    **Next,
    ACPI_OBJECT_TYPE        *ReturnType)
{
    char                    *Start;
    UINT32                  Depth;
    ACPI_OBJECT_TYPE        Type = ACPI_TYPE_INTEGER;


    /* At end of buffer? */

    if (!String || !(*String))
    {
        return (NULL);
    }

    /* Remove any spaces at the beginning */

    if (*String == ' ')
    {
        while (*String && (*String == ' '))
        {
            String++;
        }

        if (!(*String))
        {
            return (NULL);
        }
    }

    switch (*String)
    {
    case '"':

        /* This is a quoted string, scan until closing quote */

        String++;
        Start = String;
        Type = ACPI_TYPE_STRING;

        /* Find end of string */

        while (*String && (*String != '"'))
        {
            String++;
        }
        break;

    case '(':

        /* This is the start of a buffer, scan until closing paren */

        String++;
        Start = String;
        Type = ACPI_TYPE_BUFFER;

        /* Find end of buffer */

        while (*String && (*String != ')'))
        {
            String++;
        }
        break;

    case '{':

        /* This is the start of a field unit, scan until closing brace */

        String++;
        Start = String;
        Type = ACPI_TYPE_FIELD_UNIT;

        /* Find end of buffer */

        while (*String && (*String != '}'))
        {
            String++;
        }
        break;

    case '[':

        /* This is the start of a package, scan until closing bracket */

        String++;
        Depth = 1;
        Start = String;
        Type = ACPI_TYPE_PACKAGE;

        /* Find end of package (closing bracket) */

        while (*String)
        {
            /* Handle String package elements */

            if (*String == '"')
            {
                /* Find end of string */

                String++;
                while (*String && (*String != '"'))
                {
                    String++;
                }
                if (!(*String))
                {
                    break;
                }
            }
            else if (*String == '[')
            {
                Depth++;         /* A nested package declaration */
            }
            else if (*String == ']')
            {
                Depth--;
                if (Depth == 0) /* Found final package closing bracket */
                {
                    break;
                }
            }

            String++;
        }
        break;

    default:

        Start = String;

        /* Find end of token */

        while (*String && (*String != ' '))
        {
            String++;
        }
        break;
    }

    if (!(*String))
    {
        *Next = NULL;
    }
    else
    {
        *String = 0;
        *Next = String + 1;
    }

    *ReturnType = Type;
    return (Start);
}