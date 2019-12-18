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
typedef  int /*<<< orphan*/  shellpath ;
typedef  int /*<<< orphan*/  paths ;

/* Variables and functions */
 int /*<<< orphan*/  EX_CONFIG ; 
 int /*<<< orphan*/  EX_OSFILE ; 
 int /*<<< orphan*/  X_OK ; 
 int _UC_MAXLINE ; 
 int _UC_MAXSHELLS ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static char *
shell_path(char const * path, char *shells[], char *sh)
{
	if (sh != NULL && (*sh == '/' || *sh == '\0'))
		return sh;	/* specified full path or forced none */
	else {
		char           *p;
		char            paths[_UC_MAXLINE];

		/*
		 * We need to search paths
		 */
		strlcpy(paths, path, sizeof(paths));
		for (p = strtok(paths, ": \t\r\n"); p != NULL; p = strtok(NULL, ": \t\r\n")) {
			int             i;
			static char     shellpath[256];

			if (sh != NULL) {
				snprintf(shellpath, sizeof(shellpath), "%s/%s", p, sh);
				if (access(shellpath, X_OK) == 0)
					return shellpath;
			} else
				for (i = 0; i < _UC_MAXSHELLS && shells[i] != NULL; i++) {
					snprintf(shellpath, sizeof(shellpath), "%s/%s", p, shells[i]);
					if (access(shellpath, X_OK) == 0)
						return shellpath;
				}
		}
		if (sh == NULL)
			errx(EX_OSFILE, "can't find shell `%s' in shell paths", sh);
		errx(EX_CONFIG, "no default shell available or defined");
		return NULL;
	}
}