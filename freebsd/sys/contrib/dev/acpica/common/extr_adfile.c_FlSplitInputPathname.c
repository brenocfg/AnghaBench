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
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 char* FlStrdup (char*) ; 
 int /*<<< orphan*/  UtConvertBackslashes (char*) ; 
 char* strrchr (char*,char) ; 

ACPI_STATUS
FlSplitInputPathname (
    char                    *InputPath,
    char                    **OutDirectoryPath,
    char                    **OutFilename)
{
    char                    *Substring;
    char                    *DirectoryPath;
    char                    *Filename;


    if (OutDirectoryPath)
    {
        *OutDirectoryPath = NULL;
    }

    if (!InputPath)
    {
        return (AE_OK);
    }

    /* Get the path to the input filename's directory */

    DirectoryPath = FlStrdup (InputPath);
    if (!DirectoryPath)
    {
        return (AE_NO_MEMORY);
    }

    /* Convert backslashes to slashes in the entire path */

    UtConvertBackslashes (DirectoryPath);

    /* Backup to last slash or colon */

    Substring = strrchr (DirectoryPath, '/');
    if (!Substring)
    {
        Substring = strrchr (DirectoryPath, ':');
    }

    /* Extract the simple filename */

    if (!Substring)
    {
        Filename = FlStrdup (DirectoryPath);
        DirectoryPath[0] = 0;
    }
    else
    {
        Filename = FlStrdup (Substring + 1);
        *(Substring+1) = 0;
    }

    if (!Filename)
    {
        return (AE_NO_MEMORY);
    }

    if (OutDirectoryPath)
    {
        *OutDirectoryPath = DirectoryPath;
    }

    if (OutFilename)
    {
        *OutFilename = Filename;
        return (AE_OK);
    }

    return (AE_OK);
}