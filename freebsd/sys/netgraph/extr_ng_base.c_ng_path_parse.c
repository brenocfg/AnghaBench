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
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 

int
ng_path_parse(char *addr, char **nodep, char **pathp, char **hookp)
{
	char	*node, *path, *hook;
	int	k;

	/*
	 * Extract absolute NODE, if any
	 */
	for (path = addr; *path && *path != ':'; path++);
	if (*path) {
		node = addr;	/* Here's the NODE */
		*path++ = '\0';	/* Here's the PATH */

		/* Node name must not be empty */
		if (!*node)
			return -1;

		/* A name of "." is OK; otherwise '.' not allowed */
		if (strcmp(node, ".") != 0) {
			for (k = 0; node[k]; k++)
				if (node[k] == '.')
					return -1;
		}
	} else {
		node = NULL;	/* No absolute NODE */
		path = addr;	/* Here's the PATH */
	}

	/* Snoop for illegal characters in PATH */
	for (k = 0; path[k]; k++)
		if (path[k] == ':')
			return -1;

	/* Check for no repeated dots in PATH */
	for (k = 0; path[k]; k++)
		if (path[k] == '.' && path[k + 1] == '.')
			return -1;

	/* Remove extra (degenerate) dots from beginning or end of PATH */
	if (path[0] == '.')
		path++;
	if (*path && path[strlen(path) - 1] == '.')
		path[strlen(path) - 1] = 0;

	/* If PATH has a dot, then we're not talking about a hook */
	if (*path) {
		for (hook = path, k = 0; path[k]; k++)
			if (path[k] == '.') {
				hook = NULL;
				break;
			}
	} else
		path = hook = NULL;

	/* Done */
	if (nodep)
		*nodep = node;
	if (pathp)
		*pathp = path;
	if (hookp)
		*hookp = hook;
	return (0);
}