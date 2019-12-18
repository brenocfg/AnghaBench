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
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  are_symlinks_supported (char const*) ; 
 scalar_t__ git_config_delete_entry (int /*<<< orphan*/ *,char*) ; 
 int git_config_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int git_path_does_fs_decompose_unicode (char const*) ; 
 int is_chmod_supported (char const*) ; 
 scalar_t__ is_filesystem_case_insensitive (char const*) ; 

__attribute__((used)) static int repo_init_fs_configs(
	git_config *cfg,
	const char *cfg_path,
	const char *repo_dir,
	const char *work_dir,
	bool update_ignorecase)
{
	int error = 0;

	if (!work_dir)
		work_dir = repo_dir;

	if ((error = git_config_set_bool(
			cfg, "core.filemode", is_chmod_supported(cfg_path))) < 0)
		return error;

	if (!are_symlinks_supported(work_dir)) {
		if ((error = git_config_set_bool(cfg, "core.symlinks", false)) < 0)
			return error;
	} else if (git_config_delete_entry(cfg, "core.symlinks") < 0)
		git_error_clear();

	if (update_ignorecase) {
		if (is_filesystem_case_insensitive(repo_dir)) {
			if ((error = git_config_set_bool(cfg, "core.ignorecase", true)) < 0)
				return error;
		} else if (git_config_delete_entry(cfg, "core.ignorecase") < 0)
			git_error_clear();
	}

#ifdef GIT_USE_ICONV
	if ((error = git_config_set_bool(
			cfg, "core.precomposeunicode",
			git_path_does_fs_decompose_unicode(work_dir))) < 0)
		return error;
	/* on non-iconv platforms, don't even set core.precomposeunicode */
#endif

	return 0;
}