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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_REMOTE_ORIGIN ; 
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clar_sandbox_path () ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_remote_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 char* git_repository_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_set_workdir (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void populate_symlink_workdir(void)
{
	git_buf path = GIT_BUF_INIT;
	git_repository *repo;
	git_remote *origin;
	git_object *target;

	const char *url = git_repository_path(g_repo);

	cl_git_pass(git_buf_joinpath(&path, clar_sandbox_path(), "symlink.git"));
	cl_git_pass(git_repository_init(&repo, path.ptr, true));
	cl_git_pass(git_repository_set_workdir(repo, "symlink", 1));

	/* Delete the `origin` repo (if it exists) so we can recreate it. */
	git_remote_delete(repo, GIT_REMOTE_ORIGIN);

	cl_git_pass(git_remote_create(&origin, repo, GIT_REMOTE_ORIGIN, url));
	cl_git_pass(git_remote_fetch(origin, NULL, NULL, NULL));
	git_remote_free(origin);

	cl_git_pass(git_revparse_single(&target, repo, "remotes/origin/master"));
	cl_git_pass(git_reset(repo, target, GIT_RESET_HARD, NULL));

	git_object_free(target);
	git_repository_free(repo);
	git_buf_dispose(&path);
}