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
typedef  int /*<<< orphan*/  git_submodule ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_create_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_repo ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ *) ; 
 char* git_submodule_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_repo_init (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int make_submodule_dirty(git_submodule *sm, const char *name, void *payload)
{
	git_buf submodulepath = GIT_BUF_INIT;
	git_buf dirtypath = GIT_BUF_INIT;
	git_repository *submodule_repo;

	GIT_UNUSED(name);
	GIT_UNUSED(payload);

	/* remove submodule directory in preparation for init and repo_init */
	cl_git_pass(git_buf_joinpath(
		&submodulepath,
		git_repository_workdir(g_repo),
		git_submodule_path(sm)
	));
	git_futils_rmdir_r(git_buf_cstr(&submodulepath), NULL, GIT_RMDIR_REMOVE_FILES);

	/* initialize submodule's repository */
	cl_git_pass(git_submodule_repo_init(&submodule_repo, sm, 0));

	/* create a file in the submodule workdir to make it dirty */
	cl_git_pass(
		git_buf_joinpath(&dirtypath, git_repository_workdir(submodule_repo), "dirty"));
	force_create_file(git_buf_cstr(&dirtypath));

	git_buf_dispose(&dirtypath);
	git_buf_dispose(&submodulepath);
	git_repository_free(submodule_repo);

	return 0;
}