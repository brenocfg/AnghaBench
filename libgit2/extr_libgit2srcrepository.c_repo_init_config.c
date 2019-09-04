#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_7__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int GIT_REPOSITORY_INIT_BARE ; 
 int GIT_REPOSITORY_INIT_RELATIVE_GITLINK ; 
 int GIT_REPOSITORY_INIT_SHARED_ALL ; 
 int GIT_REPOSITORY_INIT_SHARED_GROUP ; 
 int GIT_REPOSITORY_INIT__IS_REINIT ; 
 int GIT_REPOSITORY_INIT__NATURAL_WD ; 
 int GIT_REPO_VERSION ; 
 int check_repositoryformatversion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_buf_sets (TYPE_1__*,char const*) ; 
 scalar_t__ git_config_delete_entry (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int git_config_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int git_config_set_int32 (int /*<<< orphan*/ *,char*,int) ; 
 int git_config_set_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int git_path_make_relative (TYPE_1__*,char const*) ; 
 int repo_init_fs_configs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int) ; 
 int repo_local_config (int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int repo_init_config(
	const char *repo_dir,
	const char *work_dir,
	uint32_t flags,
	uint32_t mode)
{
	int error = 0;
	git_buf cfg_path = GIT_BUF_INIT, worktree_path = GIT_BUF_INIT;
	git_config *config = NULL;
	bool is_bare = ((flags & GIT_REPOSITORY_INIT_BARE) != 0);
	bool is_reinit = ((flags & GIT_REPOSITORY_INIT__IS_REINIT) != 0);

	if ((error = repo_local_config(&config, &cfg_path, NULL, repo_dir)) < 0)
		goto cleanup;

	if (is_reinit && (error = check_repositoryformatversion(config)) < 0)
		goto cleanup;

#define SET_REPO_CONFIG(TYPE, NAME, VAL) do { \
	if ((error = git_config_set_##TYPE(config, NAME, VAL)) < 0) \
		goto cleanup; } while (0)

	SET_REPO_CONFIG(bool, "core.bare", is_bare);
	SET_REPO_CONFIG(int32, "core.repositoryformatversion", GIT_REPO_VERSION);

	if ((error = repo_init_fs_configs(
			config, cfg_path.ptr, repo_dir, work_dir, !is_reinit)) < 0)
		goto cleanup;

	if (!is_bare) {
		SET_REPO_CONFIG(bool, "core.logallrefupdates", true);

		if (!(flags & GIT_REPOSITORY_INIT__NATURAL_WD)) {
			if ((error = git_buf_sets(&worktree_path, work_dir)) < 0)
				goto cleanup;

			if ((flags & GIT_REPOSITORY_INIT_RELATIVE_GITLINK))
				if ((error = git_path_make_relative(&worktree_path, repo_dir)) < 0)
					goto cleanup;

			SET_REPO_CONFIG(string, "core.worktree", worktree_path.ptr);
		} else if (is_reinit) {
			if (git_config_delete_entry(config, "core.worktree") < 0)
				git_error_clear();
		}
	}

	if (mode == GIT_REPOSITORY_INIT_SHARED_GROUP) {
		SET_REPO_CONFIG(int32, "core.sharedrepository", 1);
		SET_REPO_CONFIG(bool, "receive.denyNonFastforwards", true);
	}
	else if (mode == GIT_REPOSITORY_INIT_SHARED_ALL) {
		SET_REPO_CONFIG(int32, "core.sharedrepository", 2);
		SET_REPO_CONFIG(bool, "receive.denyNonFastforwards", true);
	}

cleanup:
	git_buf_dispose(&cfg_path);
	git_buf_dispose(&worktree_path);
	git_config_free(config);

	return error;
}