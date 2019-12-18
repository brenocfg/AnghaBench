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
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_repository_get_namespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_set_namespace (int /*<<< orphan*/ ,char*) ; 

void test_refs_namespaces__get_and_set(void)
{
	cl_assert_equal_s(NULL, git_repository_get_namespace(g_repo));

	cl_git_pass(git_repository_set_namespace(g_repo, "namespace"));
	cl_assert_equal_s("namespace", git_repository_get_namespace(g_repo));

	cl_git_pass(git_repository_set_namespace(g_repo, NULL));
	cl_assert_equal_s(NULL, git_repository_get_namespace(g_repo));
}