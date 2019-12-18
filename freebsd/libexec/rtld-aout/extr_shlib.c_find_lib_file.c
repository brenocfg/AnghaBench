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

/* Variables and functions */
 char* concat (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int lstat (char*,struct stat*) ; 
 int n_search_dirs ; 
 int /*<<< orphan*/ * search_dirs ; 

char *
find_lib_file(const char *name)
{
	int		i;

	for (i = 0; i < n_search_dirs; i++) {
		char		*path = concat(search_dirs[i], "/", name);
		struct stat	sb;

		if (lstat(path, &sb) != -1)	/* We found it */
			return path;

		free(path);
	}

	return NULL;
}