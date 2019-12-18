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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (char const*,char*,int) ; 
 char** emptyextlist ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *
file_lookup(const char *path, const char *name, int namelen, char **extlist)
{
	struct stat	st;
	char	*result, *cp, **cpp;
	int		pathlen, extlen, len;

	pathlen = strlen(path);
	extlen = 0;
	if (extlist == NULL)
		extlist = emptyextlist;
	for (cpp = extlist; *cpp; cpp++) {
		len = strlen(*cpp);
		if (len > extlen)
			extlen = len;
	}
	result = malloc(pathlen + namelen + extlen + 2);
	if (result == NULL)
		return (NULL);
	bcopy(path, result, pathlen);
	if (pathlen > 0 && result[pathlen - 1] != '/')
		result[pathlen++] = '/';
	cp = result + pathlen;
	bcopy(name, cp, namelen);
	cp += namelen;
	for (cpp = extlist; *cpp; cpp++) {
		strcpy(cp, *cpp);
		if (stat(result, &st) == 0 && S_ISREG(st.st_mode))
			return result;
	}
	free(result);
	return NULL;
}