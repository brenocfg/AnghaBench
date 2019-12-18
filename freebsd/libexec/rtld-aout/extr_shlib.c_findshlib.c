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
 int n_search_dirs ; 
 int /*<<< orphan*/ * search_dirs ; 
 char* search_lib_dir (int /*<<< orphan*/ ,char*,int*,int*,int) ; 

char *
findshlib(char *name, int *majorp, int *minorp, int do_dot_a)
{
	int		i;

	for (i = 0; i < n_search_dirs; i++) {
		char	*path;

		path = search_lib_dir(search_dirs[i], name, majorp, minorp,
			do_dot_a);
		if(path != NULL)
			return path;
	}

	return NULL;
}