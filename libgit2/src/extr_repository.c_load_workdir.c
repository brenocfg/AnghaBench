#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {void* workdir; int /*<<< orphan*/  gitdir; scalar_t__ is_worktree; scalar_t__ is_bare; } ;
typedef  TYPE_1__ git_repository ;
struct TYPE_16__ {scalar_t__ value; } ;
typedef  TYPE_2__ git_config_entry ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_17__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ git_buf ;

/* Variables and functions */
 TYPE_3__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (void*) ; 
 int /*<<< orphan*/  GIT_GITDIR_FILE ; 
 int /*<<< orphan*/  git_buf_attach (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 void* git_buf_detach (TYPE_3__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 int git_config__lookup_entry (TYPE_2__**,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_config_entry_free (TYPE_2__*) ; 
 scalar_t__ git_path_dirname_r (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ git_path_isdir (int /*<<< orphan*/ ) ; 
 int git_path_prettify_dir (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ git_path_to_dir (TYPE_3__*) ; 
 char* git_worktree__read_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int load_workdir(git_repository *repo, git_config *config, git_buf *parent_path)
{
	int error;
	git_config_entry *ce;
	git_buf worktree = GIT_BUF_INIT;
	git_buf path = GIT_BUF_INIT;

	if (repo->is_bare)
		return 0;

	if ((error = git_config__lookup_entry(
			&ce, config, "core.worktree", false)) < 0)
		return error;

	if (repo->is_worktree) {
		char *gitlink = git_worktree__read_link(repo->gitdir, GIT_GITDIR_FILE);
		if (!gitlink) {
			error = -1;
			goto cleanup;
		}

		git_buf_attach(&worktree, gitlink, 0);

		if ((git_path_dirname_r(&worktree, worktree.ptr)) < 0 ||
		    git_path_to_dir(&worktree) < 0) {
			error = -1;
			goto cleanup;
		}

		repo->workdir = git_buf_detach(&worktree);
	}
	else if (ce && ce->value) {
		if ((error = git_path_prettify_dir(
				&worktree, ce->value, repo->gitdir)) < 0)
			goto cleanup;

		repo->workdir = git_buf_detach(&worktree);
	}
	else if (parent_path && git_path_isdir(parent_path->ptr))
		repo->workdir = git_buf_detach(parent_path);
	else {
		if (git_path_dirname_r(&worktree, repo->gitdir) < 0 ||
		    git_path_to_dir(&worktree) < 0) {
			error = -1;
			goto cleanup;
		}

		repo->workdir = git_buf_detach(&worktree);
	}

	GIT_ERROR_CHECK_ALLOC(repo->workdir);
cleanup:
	git_buf_dispose(&path);
	git_config_entry_free(ce);
	return error;
}