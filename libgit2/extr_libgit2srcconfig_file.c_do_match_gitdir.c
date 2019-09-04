#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_10__ {char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int FNM_IGNORECASE ; 
 int FNM_LEADING_DIR ; 
 int FNM_PATHNAME ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,char*,char const*) ; 
 scalar_t__ git_buf_oom (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_buf_sets (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  git_path_dirname_r (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  git_path_is_absolute (char const*) ; 
 scalar_t__ git_path_is_dirsep (char const) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_sysdir_expand_global_file (TYPE_1__*,char const*) ; 
 int p_fnmatch (char*,int /*<<< orphan*/ ,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int do_match_gitdir(
	int *matches,
	const git_repository *repo,
	const char *cfg_file,
	const char *value,
	bool case_insensitive)
{
	git_buf path = GIT_BUF_INIT;
	int error, fnmatch_flags;

	if (value[0] == '.' && git_path_is_dirsep(value[1])) {
		git_path_dirname_r(&path, cfg_file);
		git_buf_joinpath(&path, path.ptr, value + 2);
	} else if (value[0] == '~' && git_path_is_dirsep(value[1]))
		git_sysdir_expand_global_file(&path, value + 1);
	else if (!git_path_is_absolute(value))
		git_buf_joinpath(&path, "**", value);
	else
		git_buf_sets(&path, value);

	if (git_buf_oom(&path)) {
		error = -1;
		goto out;
	}

	if (git_path_is_dirsep(value[strlen(value) - 1]))
		git_buf_puts(&path, "**");

	fnmatch_flags = FNM_PATHNAME|FNM_LEADING_DIR;
	if (case_insensitive)
		fnmatch_flags |= FNM_IGNORECASE;

	if ((error = p_fnmatch(path.ptr, git_repository_path(repo), fnmatch_flags)) < 0)
		goto out;

	*matches = (error == 0);

out:
	git_buf_dispose(&path);
	return error;
}