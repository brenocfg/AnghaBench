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
 int /*<<< orphan*/  AcpiUtStrupr (char*) ; 
 char* FlStrdup (char*) ; 
 char* strchr (char*,char) ; 
 char* strrchr (char*,char) ; 

char *
FlGetFileBasename (
    char                    *FilePathname)
{
    char                    *FileBasename;
    char                    *Substring;


    /* Backup to last slash or colon */

    Substring = strrchr (FilePathname, '/');
    if (!Substring)
    {
        Substring = strrchr (FilePathname, ':');
    }

    /* Extract the full filename (base + extension) */

    if (Substring)
    {
        FileBasename = FlStrdup (Substring + 1);
    }
    else
    {
        FileBasename = FlStrdup (FilePathname);
    }

    /* Remove the filename extension if present */

    Substring = strchr (FileBasename, '.');
    if (Substring)
    {
        *Substring = 0;
    }

    AcpiUtStrupr (FileBasename);
    return (FileBasename);
}