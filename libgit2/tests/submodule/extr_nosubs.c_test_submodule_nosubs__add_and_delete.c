#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_submodule ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_futils_readbuffer (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_submodule_add_setup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_submodule_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 

void test_submodule_nosubs__add_and_delete(void)
{
	git_repository *repo = cl_git_sandbox_init("status");
	git_submodule *sm;
	git_buf buf = GIT_BUF_INIT;

	cl_git_fail(git_submodule_lookup(NULL, repo, "libgit2"));
	cl_git_fail(git_submodule_lookup(NULL, repo, "submodules/libgit2"));

	/* create */

	cl_git_pass(git_submodule_add_setup(
		&sm, repo, "https://github.com/libgit2/libgit2.git", "submodules/libgit2", 1));
	cl_assert_equal_s("submodules/libgit2", git_submodule_name(sm));
	cl_assert_equal_s("submodules/libgit2", git_submodule_path(sm));
	git_submodule_free(sm);

	cl_git_pass(git_futils_readbuffer(&buf, "status/.gitmodules"));
	cl_assert(strstr(buf.ptr, "[submodule \"submodules/libgit2\"]") != NULL);
	cl_assert(strstr(buf.ptr, "path = submodules/libgit2") != NULL);
	git_buf_dispose(&buf);

	/* lookup */

	cl_git_fail(git_submodule_lookup(&sm, repo, "libgit2"));
	cl_git_pass(git_submodule_lookup(&sm, repo, "submodules/libgit2"));
	cl_assert_equal_s("submodules/libgit2", git_submodule_name(sm));
	cl_assert_equal_s("submodules/libgit2", git_submodule_path(sm));
	git_submodule_free(sm);

	/* update name */

	cl_git_rewritefile(
		"status/.gitmodules",
		"[submodule \"libgit2\"]\n"
		"  path = submodules/libgit2\n"
		"  url = https://github.com/libgit2/libgit2.git\n");

	cl_git_pass(git_submodule_lookup(&sm, repo, "libgit2"));
	cl_assert_equal_s("libgit2", git_submodule_name(sm));
	cl_assert_equal_s("submodules/libgit2", git_submodule_path(sm));
	git_submodule_free(sm);
	cl_git_pass(git_submodule_lookup(&sm, repo, "submodules/libgit2"));
	git_submodule_free(sm);

	/* revert name update */

	cl_git_rewritefile(
		"status/.gitmodules",
		"[submodule \"submodules/libgit2\"]\n"
		"  path = submodules/libgit2\n"
		"  url = https://github.com/libgit2/libgit2.git\n");

	cl_git_fail(git_submodule_lookup(&sm, repo, "libgit2"));
	cl_git_pass(git_submodule_lookup(&sm, repo, "submodules/libgit2"));
	git_submodule_free(sm);

	/* remove completely */

	cl_must_pass(p_unlink("status/.gitmodules"));
	cl_git_fail(git_submodule_lookup(&sm, repo, "libgit2"));
	cl_git_fail(git_submodule_lookup(&sm, repo, "submodules/libgit2"));
}