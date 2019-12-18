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
struct strbuf {int len; char const* buf; } ;
struct repository_format {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_GIT_DIR_ENVIRONMENT ; 
 int /*<<< orphan*/  GIT_WORK_TREE_ENVIRONMENT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ chdir (char const*) ; 
 scalar_t__ check_repository_format_gently (char const*,struct repository_format*,int*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getenv (int /*<<< orphan*/ ) ; 
 scalar_t__ git_work_tree_cfg ; 
 scalar_t__ inside_git_dir ; 
 int inside_work_tree ; 
 int /*<<< orphan*/  is_absolute_path (char const*) ; 
 scalar_t__ is_bare_repository_cfg ; 
 int offset_1st_component (char const*) ; 
 char const* real_path (char const*) ; 
 char* real_pathdup (char const*,int) ; 
 int /*<<< orphan*/  set_git_dir (char const*) ; 
 int /*<<< orphan*/  set_git_work_tree (char*) ; 
 char* setup_explicit_git_dir (char const*,struct strbuf*,struct repository_format*,int*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *setup_discovered_git_dir(const char *gitdir,
					    struct strbuf *cwd, int offset,
					    struct repository_format *repo_fmt,
					    int *nongit_ok)
{
	if (check_repository_format_gently(gitdir, repo_fmt, nongit_ok))
		return NULL;

	/* --work-tree is set without --git-dir; use discovered one */
	if (getenv(GIT_WORK_TREE_ENVIRONMENT) || git_work_tree_cfg) {
		char *to_free = NULL;
		const char *ret;

		if (offset != cwd->len && !is_absolute_path(gitdir))
			gitdir = to_free = real_pathdup(gitdir, 1);
		if (chdir(cwd->buf))
			die_errno(_("cannot come back to cwd"));
		ret = setup_explicit_git_dir(gitdir, cwd, repo_fmt, nongit_ok);
		free(to_free);
		return ret;
	}

	/* #16.2, #17.2, #20.2, #21.2, #24, #25, #28, #29 (see t1510) */
	if (is_bare_repository_cfg > 0) {
		set_git_dir(offset == cwd->len ? gitdir : real_path(gitdir));
		if (chdir(cwd->buf))
			die_errno(_("cannot come back to cwd"));
		return NULL;
	}

	/* #0, #1, #5, #8, #9, #12, #13 */
	set_git_work_tree(".");
	if (strcmp(gitdir, DEFAULT_GIT_DIR_ENVIRONMENT))
		set_git_dir(gitdir);
	inside_git_dir = 0;
	inside_work_tree = 1;
	if (offset >= cwd->len)
		return NULL;

	/* Make "offset" point past the '/' (already the case for root dirs) */
	if (offset != offset_1st_component(cwd->buf))
		offset++;
	/* Add a '/' at the end */
	strbuf_addch(cwd, '/');
	return cwd->buf + offset;
}