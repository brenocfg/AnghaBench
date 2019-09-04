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
#define  OLD_PERM_EVERYBODY 130 
#define  OLD_PERM_GROUP 129 
 int PERM_EVERYBODY ; 
 int PERM_GROUP ; 
#define  PERM_UMASK 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int) ; 
 scalar_t__ git_config_bool (char const*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strtol (char const*,char**,int) ; 

int git_config_perm(const char *var, const char *value)
{
	int i;
	char *endptr;

	if (value == NULL)
		return PERM_GROUP;

	if (!strcmp(value, "umask"))
		return PERM_UMASK;
	if (!strcmp(value, "group"))
		return PERM_GROUP;
	if (!strcmp(value, "all") ||
	    !strcmp(value, "world") ||
	    !strcmp(value, "everybody"))
		return PERM_EVERYBODY;

	/* Parse octal numbers */
	i = strtol(value, &endptr, 8);

	/* If not an octal number, maybe true/false? */
	if (*endptr != 0)
		return git_config_bool(var, value) ? PERM_GROUP : PERM_UMASK;

	/*
	 * Treat values 0, 1 and 2 as compatibility cases, otherwise it is
	 * a chmod value to restrict to.
	 */
	switch (i) {
	case PERM_UMASK:               /* 0 */
		return PERM_UMASK;
	case OLD_PERM_GROUP:           /* 1 */
		return PERM_GROUP;
	case OLD_PERM_EVERYBODY:       /* 2 */
		return PERM_EVERYBODY;
	}

	/* A filemode value was given: 0xxx */

	if ((i & 0600) != 0600)
		die(_("problem with core.sharedRepository filemode value "
		    "(0%.3o).\nThe owner of files must always have "
		    "read and write permissions."), i);

	/*
	 * Mask filemode value. Others can not get write permission.
	 * x flags for directories are handled separately.
	 */
	return -(i & 0666);
}