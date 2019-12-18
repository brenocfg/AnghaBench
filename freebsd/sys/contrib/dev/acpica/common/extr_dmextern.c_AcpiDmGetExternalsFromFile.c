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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ACPI_EXT_ORIGIN_FROM_FILE ; 
 int ACPI_EXT_RESOLVED_REFERENCE ; 
 int /*<<< orphan*/  ACPI_TYPE_METHOD ; 
 int /*<<< orphan*/  ASL_STRING_BUFFER_SIZE ; 
 int /*<<< orphan*/  AcpiDmAddExternalListToNamespace () ; 
 int /*<<< orphan*/  AcpiDmAddPathToExternalList (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,char*,int,...) ; 
 int /*<<< orphan*/  AslAbort () ; 
 char* AslGbl_ExternalRefFilename ; 
 int /*<<< orphan*/ * AslGbl_StringBuffer ; 
 int /*<<< orphan*/  METHOD_SEPARATORS ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strtok (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
AcpiDmGetExternalsFromFile (
    void)
{
    FILE                    *ExternalRefFile;
    char                    *Token;
    char                    *MethodName;
    UINT32                  ArgCount;
    UINT32                  ImportCount = 0;


    if (!AslGbl_ExternalRefFilename)
    {
        return;
    }

    /* Open the file */

    ExternalRefFile = fopen (AslGbl_ExternalRefFilename, "r");
    if (!ExternalRefFile)
    {
        fprintf (stderr, "Could not open external reference file \"%s\"\n",
            AslGbl_ExternalRefFilename);
        AslAbort ();
        return;
    }

    /* Each line defines a method */

    while (fgets (AslGbl_StringBuffer, ASL_STRING_BUFFER_SIZE, ExternalRefFile))
    {
        Token = strtok (AslGbl_StringBuffer, METHOD_SEPARATORS);   /* "External" */
        if (!Token)
        {
            continue;
        }

        if (strcmp (Token, "External"))
        {
            continue;
        }

        MethodName = strtok (NULL, METHOD_SEPARATORS);      /* Method namepath */
        if (!MethodName)
        {
            continue;
        }

        Token = strtok (NULL, METHOD_SEPARATORS);           /* "MethodObj" */
        if (!Token)
        {
            continue;
        }

        if (strcmp (Token, "MethodObj"))
        {
            continue;
        }

        Token = strtok (NULL, METHOD_SEPARATORS);           /* Arg count */
        if (!Token)
        {
            continue;
        }

        /* Convert arg count string to an integer */

        errno = 0;
        ArgCount = strtoul (Token, NULL, 0);
        if (errno)
        {
            fprintf (stderr, "Invalid argument count (%s)\n", Token);
            continue;
        }

        if (ArgCount > 7)
        {
            fprintf (stderr, "Invalid argument count (%u)\n", ArgCount);
            continue;
        }

        /* Add this external to the global list */

        AcpiOsPrintf ("%s: Importing method external (%u arguments) %s\n",
            AslGbl_ExternalRefFilename, ArgCount, MethodName);

        AcpiDmAddPathToExternalList (MethodName, ACPI_TYPE_METHOD,
            ArgCount, (ACPI_EXT_RESOLVED_REFERENCE | ACPI_EXT_ORIGIN_FROM_FILE));
        ImportCount++;
    }

    if (!ImportCount)
    {
        fprintf (stderr,
            "Did not find any external methods in reference file \"%s\"\n",
            AslGbl_ExternalRefFilename);
    }
    else
    {
        /* Add the external(s) to the namespace */

        AcpiDmAddExternalListToNamespace ();

        AcpiOsPrintf ("%s: Imported %u external method definitions\n",
            AslGbl_ExternalRefFilename, ImportCount);
    }

    fclose (ExternalRefFile);
}