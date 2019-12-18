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
struct TYPE_10__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 char const* GIT_REFS_HEADS_DIR ; 
 char const* GIT_SYMREF ; 
 int /*<<< orphan*/  GIT_UNUSED (char const*) ; 
 scalar_t__ WM_MATCH ; 
 int /*<<< orphan*/  WM_PATHNAME ; 
 scalar_t__ git__strncmp (scalar_t__,char const*,int) ; 
 int /*<<< orphan*/  git_buf_consume (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_buf_puts (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_buf_rtrim (TYPE_1__*) ; 
 int git_buf_sets (TYPE_1__*,char const*) ; 
 int git_futils_readbuffer (TYPE_1__*,scalar_t__) ; 
 scalar_t__ git_path_is_dirsep (char const) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/  const*) ; 
 int strlen (char const*) ; 
 scalar_t__ wildmatch (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int conditional_match_onbranch(
	int *matches,
	const git_repository *repo,
	const char *cfg_file,
	const char *condition)
{
	git_buf reference = GIT_BUF_INIT, buf = GIT_BUF_INIT;
	int error;

	GIT_UNUSED(cfg_file);

	/*
	 * NOTE: you cannot use `git_repository_head` here. Looking up the
	 * HEAD reference will create the ODB, which causes us to read the
	 * repo's config for keys like core.precomposeUnicode. As we're
	 * just parsing the config right now, though, this would result in
	 * an endless recursion.
	 */

	if ((error = git_buf_joinpath(&buf, git_repository_path(repo), GIT_HEAD_FILE)) < 0 ||
	    (error = git_futils_readbuffer(&reference, buf.ptr)) < 0)
		goto out;
	git_buf_rtrim(&reference);

	if (git__strncmp(reference.ptr, GIT_SYMREF, strlen(GIT_SYMREF)))
		goto out;
	git_buf_consume(&reference, reference.ptr + strlen(GIT_SYMREF));

	if (git__strncmp(reference.ptr, GIT_REFS_HEADS_DIR, strlen(GIT_REFS_HEADS_DIR)))
		goto out;
	git_buf_consume(&reference, reference.ptr + strlen(GIT_REFS_HEADS_DIR));

	/*
	 * If the condition ends with a '/', then we should treat it as if
	 * it had '**' appended.
	 */
	if ((error = git_buf_sets(&buf, condition)) < 0)
		goto out;
	if (git_path_is_dirsep(condition[strlen(condition) - 1]) &&
	    (error = git_buf_puts(&buf, "**")) < 0)
		goto out;

	*matches = wildmatch(buf.ptr, reference.ptr, WM_PATHNAME) == WM_MATCH;
out:
	git_buf_dispose(&reference);
	git_buf_dispose(&buf);

	return error;

}