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
 int /*<<< orphan*/  GIT_OPT_GET_SEARCH_PATH ; 
 int /*<<< orphan*/  _global_path ; 
 int /*<<< orphan*/ * _repo ; 
 int g_umask ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int p_umask (int) ; 

void test_repo_init__initialize(void)
{
	_repo = NULL;

	/* load umask if not already loaded */
	if (!g_umask) {
		g_umask = p_umask(022);
		(void)p_umask(g_umask);
	}

    git_libgit2_opts(GIT_OPT_GET_SEARCH_PATH, GIT_CONFIG_LEVEL_GLOBAL,
		&_global_path);
}