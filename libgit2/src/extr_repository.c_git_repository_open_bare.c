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
struct TYPE_5__ {int is_bare; int /*<<< orphan*/ * workdir; scalar_t__ is_worktree; struct TYPE_5__* commondir; struct TYPE_5__* gitdir; } ;
typedef  TYPE_1__ git_repository ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_ERROR_REPOSITORY ; 
 void* git_buf_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int git_path_prettify_dir (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* repository_alloc () ; 
 int /*<<< orphan*/  valid_repository_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int git_repository_open_bare(
	git_repository **repo_ptr,
	const char *bare_path)
{
	int error;
	git_buf path = GIT_BUF_INIT, common_path = GIT_BUF_INIT;
	git_repository *repo = NULL;

	if ((error = git_path_prettify_dir(&path, bare_path, NULL)) < 0)
		return error;

	if (!valid_repository_path(&path, &common_path)) {
		git_buf_dispose(&path);
		git_buf_dispose(&common_path);
		git_error_set(GIT_ERROR_REPOSITORY, "path is not a repository: %s", bare_path);
		return GIT_ENOTFOUND;
	}

	repo = repository_alloc();
	GIT_ERROR_CHECK_ALLOC(repo);

	repo->gitdir = git_buf_detach(&path);
	GIT_ERROR_CHECK_ALLOC(repo->gitdir);
	repo->commondir = git_buf_detach(&common_path);
	GIT_ERROR_CHECK_ALLOC(repo->commondir);

	/* of course we're bare! */
	repo->is_bare = 1;
	repo->is_worktree = 0;
	repo->workdir = NULL;

	*repo_ptr = repo;
	return 0;
}