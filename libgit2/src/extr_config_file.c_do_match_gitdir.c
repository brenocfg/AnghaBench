#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_12__ {char* ptr; int size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_REPOSITORY_ITEM_GITDIR ; 
 int WM_CASEFOLD ; 
 scalar_t__ WM_MATCH ; 
 int WM_PATHNAME ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,char*,char const*) ; 
 scalar_t__ git_buf_oom (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_buf_sets (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  git_buf_truncate (TYPE_1__*,int) ; 
 int /*<<< orphan*/  git_path_dirname_r (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  git_path_is_absolute (char const*) ; 
 scalar_t__ git_path_is_dirsep (char const) ; 
 int git_repository_item_path (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_sysdir_expand_global_file (TYPE_1__*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ wildmatch (char const*,char const*,int) ; 

__attribute__((used)) static int do_match_gitdir(
	int *matches,
	const git_repository *repo,
	const char *cfg_file,
	const char *condition,
	bool case_insensitive)
{
	git_buf pattern = GIT_BUF_INIT, gitdir = GIT_BUF_INIT;
	int error;

	if (condition[0] == '.' && git_path_is_dirsep(condition[1])) {
		git_path_dirname_r(&pattern, cfg_file);
		git_buf_joinpath(&pattern, pattern.ptr, condition + 2);
	} else if (condition[0] == '~' && git_path_is_dirsep(condition[1]))
		git_sysdir_expand_global_file(&pattern, condition + 1);
	else if (!git_path_is_absolute(condition))
		git_buf_joinpath(&pattern, "**", condition);
	else
		git_buf_sets(&pattern, condition);

	if (git_path_is_dirsep(condition[strlen(condition) - 1]))
		git_buf_puts(&pattern, "**");

	if (git_buf_oom(&pattern)) {
		error = -1;
		goto out;
	}

	if ((error = git_repository_item_path(&gitdir, repo, GIT_REPOSITORY_ITEM_GITDIR)) < 0)
		goto out;

	if (git_path_is_dirsep(gitdir.ptr[gitdir.size - 1]))
		git_buf_truncate(&gitdir, gitdir.size - 1);

	*matches = wildmatch(pattern.ptr, gitdir.ptr,
			     WM_PATHNAME | (case_insensitive ? WM_CASEFOLD : 0)) == WM_MATCH;
out:
	git_buf_dispose(&pattern);
	git_buf_dispose(&gitdir);
	return error;
}