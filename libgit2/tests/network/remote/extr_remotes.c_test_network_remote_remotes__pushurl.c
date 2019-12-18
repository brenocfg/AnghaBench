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
typedef  int /*<<< orphan*/  git_remote ;

/* Variables and functions */
 int /*<<< orphan*/  _remote ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*) ; 
 char* git_remote_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_remote_pushurl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_set_pushurl (int /*<<< orphan*/ ,char const*,char*) ; 

void test_network_remote_remotes__pushurl(void)
{
	const char *name = git_remote_name(_remote);
	git_remote *mod;

	cl_git_pass(git_remote_set_pushurl(_repo, name, "git://github.com/libgit2/notlibgit2"));
	cl_git_pass(git_remote_lookup(&mod, _repo, name));
	cl_assert_equal_s(git_remote_pushurl(mod), "git://github.com/libgit2/notlibgit2");
	git_remote_free(mod);

	cl_git_pass(git_remote_set_pushurl(_repo, name, NULL));
	cl_git_pass(git_remote_lookup(&mod, _repo, name));
	cl_assert(git_remote_pushurl(mod) == NULL);
	git_remote_free(mod);
}