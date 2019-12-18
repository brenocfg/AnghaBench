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
typedef  scalar_t__ ACPI_SIZE ;

/* Variables and functions */
 char* UtLocalCacheCalloc (scalar_t__) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 char* strrchr (char*,char) ; 

char *
FlGenerateFilename (
    char                    *InputFilename,
    char                    *Suffix)
{
    char                    *Position;
    char                    *NewFilename;
    char                    *DirectoryPosition;


    /*
     * Copy the original filename to a new buffer. Leave room for the worst
     * case where we append the suffix, an added dot and the null terminator.
     */
    NewFilename = UtLocalCacheCalloc ((ACPI_SIZE)
        strlen (InputFilename) + strlen (Suffix) + 2);
    strcpy (NewFilename, InputFilename);

    /* Try to find the last dot in the filename */

    DirectoryPosition = strrchr (NewFilename, '/');
    Position = strrchr (NewFilename, '.');

    if (Position && (Position > DirectoryPosition))
    {
        /* Tack on the new suffix */

        Position++;
        *Position = 0;
        strcat (Position, Suffix);
    }
    else
    {
        /* No dot, add one and then the suffix */

        strcat (NewFilename, ".");
        strcat (NewFilename, Suffix);
    }

    return (NewFilename);
}