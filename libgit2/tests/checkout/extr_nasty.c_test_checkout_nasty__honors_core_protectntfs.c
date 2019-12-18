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
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  test_checkout_fails (char*,char*) ; 

void test_checkout_nasty__honors_core_protectntfs(void)
{
	cl_repo_set_bool(repo, "core.protectNTFS", true);

	test_checkout_fails("refs/heads/dotgit_backslash_path", ".git/foobar");
	test_checkout_fails("refs/heads/dotcapitalgit_backslash_path", ".GIT/foobar");
	test_checkout_fails("refs/heads/dot_git_dot", ".git/foobar");
	test_checkout_fails("refs/heads/git_tilde1", ".git/foobar");
}