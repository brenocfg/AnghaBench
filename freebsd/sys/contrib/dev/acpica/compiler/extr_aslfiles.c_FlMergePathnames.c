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

/* Variables and functions */
 int /*<<< orphan*/  ASL_PARSE_OUTPUT ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  UtConvertBackslashes (char*) ; 
 char* UtLocalCacheCalloc (scalar_t__) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 char* strrchr (char*,char) ; 

char *
FlMergePathnames (
    char                    *PrefixDir,
    char                    *FilePathname)
{
    char                    *CommonPath;
    char                    *Pathname;
    char                    *LastElement;


    DbgPrint (ASL_PARSE_OUTPUT, "Include: Prefix path - \"%s\"\n"
        "Include: FilePathname - \"%s\"\n",
         PrefixDir, FilePathname);

    /*
     * If there is no prefix directory or if the file pathname is absolute,
     * just return the original file pathname
     */
    if (!PrefixDir || (!*PrefixDir) ||
        (*FilePathname == '/') ||
         (FilePathname[1] == ':'))
    {
        Pathname = UtLocalCacheCalloc (strlen (FilePathname) + 1);
        strcpy (Pathname, FilePathname);
        goto ConvertBackslashes;
    }

    /* Need a local copy of the prefix directory path */

    CommonPath = UtLocalCacheCalloc (strlen (PrefixDir) + 1);
    strcpy (CommonPath, PrefixDir);

    /*
     * Walk forward through the file path, and simultaneously backward
     * through the prefix directory path until there are no more
     * relative references at the start of the file path.
     */
    while (*FilePathname && (!strncmp (FilePathname, "../", 3)))
    {
        /* Remove last element of the prefix directory path */

        LastElement = strrchr (CommonPath, '/');
        if (!LastElement)
        {
            goto ConcatenatePaths;
        }

        *LastElement = 0;   /* Terminate CommonPath string */
        FilePathname += 3;  /* Point to next path element */
    }

    /*
     * Remove the last element of the prefix directory path (it is the same as
     * the first element of the file pathname), and build the final merged
     * pathname.
     */
    LastElement = strrchr (CommonPath, '/');
    if (LastElement)
    {
        *LastElement = 0;
    }

    /* Build the final merged pathname */

ConcatenatePaths:
    Pathname = UtLocalCacheCalloc (
        strlen (CommonPath) + strlen (FilePathname) + 2);
    if (LastElement && *CommonPath)
    {
        strcpy (Pathname, CommonPath);
        strcat (Pathname, "/");
    }
    strcat (Pathname, FilePathname);

    /* Convert all backslashes to normal slashes */

ConvertBackslashes:
    UtConvertBackslashes (Pathname);

    DbgPrint (ASL_PARSE_OUTPUT, "Include: Merged Pathname - \"%s\"\n",
         Pathname);
    return (Pathname);
}