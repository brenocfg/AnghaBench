#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {unsigned int is_worktree; int is_bare; struct TYPE_20__* commondir; struct TYPE_20__* gitlink; struct TYPE_20__* gitdir; } ;
typedef  TYPE_1__ git_repository ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_21__ {scalar_t__ size; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 unsigned int GIT_REPOSITORY_OPEN_BARE ; 
 unsigned int GIT_REPOSITORY_OPEN_FROM_ENV ; 
 int _git_repository_open_ext_from_env (TYPE_1__**,char const*) ; 
 int check_repositoryformatversion (int /*<<< orphan*/ *) ; 
 int find_repo (TYPE_2__*,TYPE_2__*,TYPE_2__*,TYPE_2__*,char const*,unsigned int,char const*) ; 
 void* git_buf_detach (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int git_repository_config_snapshot (int /*<<< orphan*/ **,TYPE_1__*) ; 
 int /*<<< orphan*/  git_repository_free (TYPE_1__*) ; 
 int load_config_data (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int load_workdir (TYPE_1__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int repo_is_worktree (unsigned int*,TYPE_1__*) ; 
 TYPE_1__* repository_alloc () ; 

int git_repository_open_ext(
	git_repository **repo_ptr,
	const char *start_path,
	unsigned int flags,
	const char *ceiling_dirs)
{
	int error;
	unsigned is_worktree;
	git_buf gitdir = GIT_BUF_INIT, workdir = GIT_BUF_INIT,
		gitlink = GIT_BUF_INIT, commondir = GIT_BUF_INIT;
	git_repository *repo = NULL;
	git_config *config = NULL;

	if (flags & GIT_REPOSITORY_OPEN_FROM_ENV)
		return _git_repository_open_ext_from_env(repo_ptr, start_path);

	if (repo_ptr)
		*repo_ptr = NULL;

	error = find_repo(
		&gitdir, &workdir, &gitlink, &commondir, start_path, flags, ceiling_dirs);

	if (error < 0 || !repo_ptr)
		goto cleanup;

	repo = repository_alloc();
	GIT_ERROR_CHECK_ALLOC(repo);

	repo->gitdir = git_buf_detach(&gitdir);
	GIT_ERROR_CHECK_ALLOC(repo->gitdir);

	if (gitlink.size) {
		repo->gitlink = git_buf_detach(&gitlink);
		GIT_ERROR_CHECK_ALLOC(repo->gitlink);
	}
	if (commondir.size) {
		repo->commondir = git_buf_detach(&commondir);
		GIT_ERROR_CHECK_ALLOC(repo->commondir);
	}

	if ((error = repo_is_worktree(&is_worktree, repo)) < 0)
		goto cleanup;
	repo->is_worktree = is_worktree;

	/*
	 * We'd like to have the config, but git doesn't particularly
	 * care if it's not there, so we need to deal with that.
	 */

	error = git_repository_config_snapshot(&config, repo);
	if (error < 0 && error != GIT_ENOTFOUND)
		goto cleanup;

	if (config && (error = check_repositoryformatversion(config)) < 0)
		goto cleanup;

	if ((flags & GIT_REPOSITORY_OPEN_BARE) != 0)
		repo->is_bare = 1;
	else {

		if (config &&
		    ((error = load_config_data(repo, config)) < 0 ||
		     (error = load_workdir(repo, config, &workdir)) < 0))
			goto cleanup;
	}

cleanup:
	git_buf_dispose(&gitdir);
	git_buf_dispose(&workdir);
	git_buf_dispose(&gitlink);
	git_buf_dispose(&commondir);
	git_config_free(config);

	if (error < 0)
		git_repository_free(repo);

	if (repo_ptr)
		*repo_ptr = repo;

	return error;
}