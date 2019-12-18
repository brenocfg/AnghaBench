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
 int /*<<< orphan*/  git__free (char*) ; 
 int git_futils_fsync_dir (char*) ; 
 char* git_path_dirname (char const*) ; 

int git_futils_fsync_parent(const char *path)
{
	char *parent;
	int error;

	if ((parent = git_path_dirname(path)) == NULL)
		return -1;

	error = git_futils_fsync_dir(parent);
	git__free(parent);
	return error;
}