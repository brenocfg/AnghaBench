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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REMOTE_ORIGIN ; 
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_remote_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int) ; 
 char* git_repository_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_set_workdir (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void populate_symlink_workdir(void)
{
	git_repository *repo;
	git_remote *origin;
	git_object *target;

	const char *url = git_repository_path(g_repo);

	cl_git_pass(git_repository_init(&repo, "../symlink.git", true));
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
}