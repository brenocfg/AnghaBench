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
typedef  int /*<<< orphan*/  parentdirbuf ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_MAX ; 
 char* dirname (char*) ; 
 int /*<<< orphan*/ * realpath (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,size_t) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

int
fileindir(const char *file, const char *dir)
{
	char	parentdirbuf[PATH_MAX+1], *parentdir;
	char	realdir[PATH_MAX+1];
	size_t	dirlen;

					/* determine parent directory of file */
	(void)strlcpy(parentdirbuf, file, sizeof(parentdirbuf));
	parentdir = dirname(parentdirbuf);
	if (strcmp(parentdir, ".") == 0)
		return 1;		/* current directory is ok */

					/* find the directory */
	if (realpath(parentdir, realdir) == NULL) {
		warn("Unable to determine real path of `%s'", parentdir);
		return 0;
	}
	if (realdir[0] != '/')		/* relative result is ok */
		return 1;
	dirlen = strlen(dir);
	if (strncmp(realdir, dir, dirlen) == 0 &&
	    (realdir[dirlen] == '/' || realdir[dirlen] == '\0'))
		return 1;
	return 0;
}