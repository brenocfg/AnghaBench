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
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  dewey ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int MAXDEWEY ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enter (char*,char*,char*,int*,int) ; 
 scalar_t__ errno ; 
 int getdewey (int*,char*) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

int
dodir(char *dir, int silent)
{
	DIR		*dd;
	struct dirent	*dp;
	char		name[MAXPATHLEN];
	int		dewey[MAXDEWEY], ndewey;

	if ((dd = opendir(dir)) == NULL) {
		if (silent && errno == ENOENT)	/* Ignore the error */
			return 0;
		warn("%s", dir);
		return -1;
	}

	while ((dp = readdir(dd)) != NULL) {
		int n;
		char *cp;

		/* Check for `lib' prefix */
		if (dp->d_name[0] != 'l' ||
		    dp->d_name[1] != 'i' ||
		    dp->d_name[2] != 'b')
			continue;

		/* Copy the entry minus prefix */
		(void)strcpy(name, dp->d_name + 3);
		n = strlen(name);
		if (n < 4)
			continue;

		/* Find ".so." in name */
		for (cp = name + n - 4; cp > name; --cp) {
			if (cp[0] == '.' &&
			    cp[1] == 's' &&
			    cp[2] == 'o' &&
			    cp[3] == '.')
				break;
		}
		if (cp <= name)
			continue;

		*cp = '\0';
		if (!isdigit(*(cp+4)))
			continue;

		bzero((caddr_t)dewey, sizeof(dewey));
		ndewey = getdewey(dewey, cp + 4);
		if (ndewey < 2)
			continue;
		enter(dir, dp->d_name, name, dewey, ndewey);
	}

	closedir(dd);
	return 0;
}