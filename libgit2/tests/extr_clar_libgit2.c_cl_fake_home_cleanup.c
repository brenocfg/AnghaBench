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
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_GLOBAL ; 
 int /*<<< orphan*/  GIT_OPT_SET_SEARCH_PATH ; 
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 char* _cl_restore_home ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void cl_fake_home_cleanup(void *payload)
{
	char *restore = _cl_restore_home;
	_cl_restore_home = NULL;

	GIT_UNUSED(payload);

	if (restore) {
		cl_git_pass(git_libgit2_opts(
			GIT_OPT_SET_SEARCH_PATH, GIT_CONFIG_LEVEL_GLOBAL, restore));
		git__free(restore);
	}
}