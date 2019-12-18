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
 int /*<<< orphan*/  AGFREE (char const*) ; 
#define  DIRCH 129 
#define  NUL 128 
 int /*<<< orphan*/  getenv (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* pathfind (int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/ * strchr (char const*,int const) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 unsigned int strlen (char const*) ; 
 char* strrchr (char const*,int const) ; 

__attribute__((used)) static bool
add_prog_path(char * buf, int b_sz, char const * fname, char const * prg_path)
{
    char const *   path;
    char const *   pz;
    int     skip = 2;

    switch (fname[2]) {
    case DIRCH:
        skip = 3;
    case NUL:
        break;
    default:
        return false;
    }

    /*
     *  See if the path is included in the program name.
     *  If it is, we're done.  Otherwise, we have to hunt
     *  for the program using "pathfind".
     */
    if (strchr(prg_path, DIRCH) != NULL)
        path = prg_path;
    else {
        path = pathfind(getenv("PATH"), prg_path, "rx");

        if (path == NULL)
            return false;
    }

    pz = strrchr(path, DIRCH);

    /*
     *  IF we cannot find a directory name separator,
     *  THEN we do not have a path name to our executable file.
     */
    if (pz == NULL)
        return false;

    fname += skip;

    /*
     *  Concatenate the file name to the end of the executable path.
     *  The result may be either a file or a directory.
     */
    if ((unsigned)(pz - path) + 1 + strlen(fname) >= (unsigned)b_sz)
        return false;

    memcpy(buf, path, (size_t)((pz - path)+1));
    strcpy(buf + (pz - path) + 1, fname);

    /*
     *  If the "path" path was gotten from "pathfind()", then it was
     *  allocated and we need to deallocate it.
     */
    if (path != prg_path)
        AGFREE(path);
    return true;
}