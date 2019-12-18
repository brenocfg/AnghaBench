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
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ resolve_gitdir_gently (char*,int*) ; 
 char* xstrfmt (char*,char const*) ; 

int is_submodule_populated_gently(const char *path, int *return_error_code)
{
	int ret = 0;
	char *gitdir = xstrfmt("%s/.git", path);

	if (resolve_gitdir_gently(gitdir, return_error_code))
		ret = 1;

	free(gitdir);
	return ret;
}