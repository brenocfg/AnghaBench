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
 int /*<<< orphan*/  GIT_OPT_ENABLE_STRICT_OBJECT_CREATION ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/  g_index ; 
 int /*<<< orphan*/ * g_repo ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,int) ; 

void test_index_add__cleanup(void)
{
	git_index_free(g_index);
	cl_git_sandbox_cleanup();
	g_repo = NULL;

	cl_git_pass(git_libgit2_opts(GIT_OPT_ENABLE_STRICT_OBJECT_CREATION, 1));
}