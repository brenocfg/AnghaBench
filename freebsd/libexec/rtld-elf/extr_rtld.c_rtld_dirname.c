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
 int PATH_MAX ; 
 int /*<<< orphan*/  _rtld_error (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static int
rtld_dirname(const char *path, char *bname)
{
    const char *endp;

    /* Empty or NULL string gets treated as "." */
    if (path == NULL || *path == '\0') {
	bname[0] = '.';
	bname[1] = '\0';
	return (0);
    }

    /* Strip trailing slashes */
    endp = path + strlen(path) - 1;
    while (endp > path && *endp == '/')
	endp--;

    /* Find the start of the dir */
    while (endp > path && *endp != '/')
	endp--;

    /* Either the dir is "/" or there are no slashes */
    if (endp == path) {
	bname[0] = *endp == '/' ? '/' : '.';
	bname[1] = '\0';
	return (0);
    } else {
	do {
	    endp--;
	} while (endp > path && *endp == '/');
    }

    if (endp - path + 2 > PATH_MAX)
    {
	_rtld_error("Filename is too long: %s", path);
	return(-1);
    }

    strncpy(bname, path, endp - path + 1);
    bname[endp - path + 1] = '\0';
    return (0);
}