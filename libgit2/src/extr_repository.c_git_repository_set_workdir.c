#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* workdir; scalar_t__ is_bare; } ;
typedef  TYPE_1__ git_repository ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_10__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int GIT_PASSTHROUGH ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 char* git_buf_detach (TYPE_2__*) ; 
 int git_config_delete_entry (int /*<<< orphan*/ *,char*) ; 
 int git_config_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int git_config_set_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ git_path_prettify_dir (TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ git_repository_config__weakptr (int /*<<< orphan*/ **,TYPE_1__*) ; 
 int /*<<< orphan*/  git_repository_path (TYPE_1__*) ; 
 int repo_write_gitlink (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

int git_repository_set_workdir(
	git_repository *repo, const char *workdir, int update_gitlink)
{
	int error = 0;
	git_buf path = GIT_BUF_INIT;

	assert(repo && workdir);

	if (git_path_prettify_dir(&path, workdir, NULL) < 0)
		return -1;

	if (repo->workdir && strcmp(repo->workdir, path.ptr) == 0)
		return 0;

	if (update_gitlink) {
		git_config *config;

		if (git_repository_config__weakptr(&config, repo) < 0)
			return -1;

		error = repo_write_gitlink(path.ptr, git_repository_path(repo), false);

		/* passthrough error means gitlink is unnecessary */
		if (error == GIT_PASSTHROUGH)
			error = git_config_delete_entry(config, "core.worktree");
		else if (!error)
			error = git_config_set_string(config, "core.worktree", path.ptr);

		if (!error)
			error = git_config_set_bool(config, "core.bare", false);
	}

	if (!error) {
		char *old_workdir = repo->workdir;

		repo->workdir = git_buf_detach(&path);
		repo->is_bare = 0;

		git__free(old_workdir);
	}

	return error;
}