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
struct stat {scalar_t__ st_dev; scalar_t__ st_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/ * realpath (char*,char*) ; 
 char* srcdir ; 
 int stat (char*,struct stat*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static void
get_srcdir(void)
{
	struct stat lg, phy;
	char *p, *pwd;
	int i;

	if (realpath("../..", srcdir) == NULL)
		err(EXIT_FAILURE, "Unable to find root of source tree");
	if ((pwd = getenv("PWD")) != NULL && *pwd == '/' &&
	    (pwd = strdup(pwd)) != NULL) {
		/* Remove the last two path components. */
		for (i = 0; i < 2; i++) {
			if ((p = strrchr(pwd, '/')) == NULL) {
				free(pwd);
				return;
			}
			*p = '\0';
		}
		if (stat(pwd, &lg) != -1 && stat(srcdir, &phy) != -1 &&
		    lg.st_dev == phy.st_dev && lg.st_ino == phy.st_ino)
			strlcpy(srcdir, pwd, MAXPATHLEN);
		free(pwd);
	}
}