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
 int /*<<< orphan*/  GIT_DIR_MODE ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fixture_url (char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  g_options ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_mkdir (char*,int /*<<< orphan*/ ) ; 

void test_clone_nonetwork__fail_with_already_existing_but_non_empty_directory(void)
{
	p_mkdir("./foo", GIT_DIR_MODE);
	cl_git_mkfile("./foo/bar", "Baz!");
	cl_git_fail(git_clone(&g_repo, cl_git_fixture_url("testrepo.git"), "./foo", &g_options));
}