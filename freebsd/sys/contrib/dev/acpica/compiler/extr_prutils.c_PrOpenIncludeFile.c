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
struct TYPE_3__ {char* Dir; struct TYPE_3__* Next; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ ASL_INCLUDE_DIR ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_INCLUDE_FILE_OPEN ; 
 int /*<<< orphan*/  AslGbl_CurrentLineOffset ; 
 char* AslGbl_DirectoryPath ; 
 TYPE_1__* AslGbl_IncludeDirList ; 
 int /*<<< orphan*/  AslGbl_MainTokenBuffer ; 
 int /*<<< orphan*/  PrError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PrOpenIncludeWithPrefix (char*,char*,char*,char**) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

FILE *
PrOpenIncludeFile (
    char                    *Filename,
    char                    *OpenMode,
    char                    **FullPathname)
{
    FILE                    *IncludeFile;
    ASL_INCLUDE_DIR         *NextDir;


    /* Start the actual include file on the next line */

    AslGbl_CurrentLineOffset++;

    /* Attempt to open the include file */
    /* If the file specifies an absolute path, just open it */

    if ((Filename[0] == '/')  ||
        (Filename[0] == '\\') ||
        (Filename[1] == ':'))
    {
        IncludeFile = PrOpenIncludeWithPrefix (
            "", Filename, OpenMode, FullPathname);
        if (!IncludeFile)
        {
            goto ErrorExit;
        }
        return (IncludeFile);
    }

    /*
     * The include filename is not an absolute path.
     *
     * First, search for the file within the "local" directory -- meaning
     * the same directory that contains the source file.
     *
     * Construct the file pathname from the global directory name.
     */
    IncludeFile = PrOpenIncludeWithPrefix (
        AslGbl_DirectoryPath, Filename, OpenMode, FullPathname);
    if (IncludeFile)
    {
        return (IncludeFile);
    }

    /*
     * Second, search for the file within the (possibly multiple)
     * directories specified by the -I option on the command line.
     */
    NextDir = AslGbl_IncludeDirList;
    while (NextDir)
    {
        IncludeFile = PrOpenIncludeWithPrefix (
            NextDir->Dir, Filename, OpenMode, FullPathname);
        if (IncludeFile)
        {
            return (IncludeFile);
        }

        NextDir = NextDir->Next;
    }

    /* We could not open the include file after trying very hard */

ErrorExit:
    sprintf (AslGbl_MainTokenBuffer, "%s, %s", Filename, strerror (errno));
    PrError (ASL_ERROR, ASL_MSG_INCLUDE_FILE_OPEN, 0);
    return (NULL);
}