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
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CONFIG_FILENAME_INREPO ; 
 int /*<<< orphan*/  GIT_CONFIG_FILE_MODE ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_LOCAL ; 
 int create_empty_file (char const*,int /*<<< orphan*/ ) ; 
 char* git_buf_cstr (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_joinpath (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int git_config_add_file_ondisk (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int git_config_open_level (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_config_open_ondisk (int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_path_isfile (char const*) ; 
 int git_repository_config__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int repo_local_config(
	git_config **out,
	git_buf *config_dir,
	git_repository *repo,
	const char *repo_dir)
{
	int error = 0;
	git_config *parent;
	const char *cfg_path;

	if (git_buf_joinpath(config_dir, repo_dir, GIT_CONFIG_FILENAME_INREPO) < 0)
		return -1;
	cfg_path = git_buf_cstr(config_dir);

	/* make LOCAL config if missing */
	if (!git_path_isfile(cfg_path) &&
		(error = create_empty_file(cfg_path, GIT_CONFIG_FILE_MODE)) < 0)
		return error;

	/* if no repo, just open that file directly */
	if (!repo)
		return git_config_open_ondisk(out, cfg_path);

	/* otherwise, open parent config and get that level */
	if ((error = git_repository_config__weakptr(&parent, repo)) < 0)
		return error;

	if (git_config_open_level(out, parent, GIT_CONFIG_LEVEL_LOCAL) < 0) {
		git_error_clear();

		if (!(error = git_config_add_file_ondisk(
				parent, cfg_path, GIT_CONFIG_LEVEL_LOCAL, repo, false)))
			error = git_config_open_level(out, parent, GIT_CONFIG_LEVEL_LOCAL);
	}

	git_config_free(parent);

	return error;
}