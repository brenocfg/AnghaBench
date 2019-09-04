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
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/ * g_object ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_path_isdir (char*) ; 

void test_checkout_tree__cleanup(void)
{
	git_object_free(g_object);
	g_object = NULL;

	cl_git_sandbox_cleanup();

	if (git_path_isdir("alternative"))
		git_futils_rmdir_r("alternative", NULL, GIT_RMDIR_REMOVE_FILES);
}