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
 int /*<<< orphan*/  add_search_dir (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char*) ; 
 char* strsep (char**,char*) ; 

void
add_search_path(char *path)
{
	register char	*cp, *dup;

	if (path == NULL)
		return;

	/* Add search directories from `path' */
	path = dup = strdup(path);
	while ((cp = strsep(&path, ":")) != NULL)
		add_search_dir(cp);
	free(dup);
}