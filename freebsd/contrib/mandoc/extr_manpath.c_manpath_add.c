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
struct stat {int dummy; } ;
struct manpaths {size_t sz; int /*<<< orphan*/ * paths; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANDOCERR_BADARG_BAD ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mandoc_reallocarray (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mandoc_strdup (char*) ; 
 char* realpath (char const*,char*) ; 
 int stat (char*,struct stat*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
manpath_add(struct manpaths *dirs, const char *dir, char option)
{
	char		 buf[PATH_MAX];
	struct stat	 sb;
	char		*cp;
	size_t		 i;

	if ((cp = realpath(dir, buf)) == NULL)
		goto fail;

	for (i = 0; i < dirs->sz; i++)
		if (strcmp(dirs->paths[i], dir) == 0)
			return;

	if (stat(cp, &sb) == -1)
		goto fail;

	dirs->paths = mandoc_reallocarray(dirs->paths,
	    dirs->sz + 1, sizeof(*dirs->paths));
	dirs->paths[dirs->sz++] = mandoc_strdup(cp);
	return;

fail:
	if (option != '\0')
		mandoc_msg(MANDOCERR_BADARG_BAD, 0, 0,
		    "-%c %s: %s", option, dir, strerror(errno));
}