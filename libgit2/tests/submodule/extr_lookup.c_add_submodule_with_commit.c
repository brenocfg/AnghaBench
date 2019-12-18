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
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  assert_submodule_exists (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  cl_git_mkfile (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_repo_commit_from_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_add_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_add_setup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_open (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_submodule_with_commit(const char *name)
{
	git_submodule *sm;
	git_repository *smrepo;
	git_index *idx;
	git_buf p = GIT_BUF_INIT;

	cl_git_pass(git_submodule_add_setup(&sm, g_repo,
		"https://github.com/libgit2/libgit2.git", name, 1));

	assert_submodule_exists(g_repo, name);

	cl_git_pass(git_submodule_open(&smrepo, sm));
	cl_git_pass(git_repository_index(&idx, smrepo));

	cl_git_pass(git_buf_joinpath(&p, git_repository_workdir(smrepo), "file"));
	cl_git_mkfile(p.ptr, "new file");
	git_buf_dispose(&p);

	cl_git_pass(git_index_add_bypath(idx, "file"));
	cl_git_pass(git_index_write(idx));
	git_index_free(idx);

	cl_repo_commit_from_index(NULL, smrepo, NULL, 0, "initial commit");
	git_repository_free(smrepo);

	cl_git_pass(git_submodule_add_finalize(sm));

	git_submodule_free(sm);
}