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
struct strbuf {int len; char* buf; } ;
struct repository_format {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_IMPLICIT_WORK_TREE_ENVIRONMENT ; 
 int /*<<< orphan*/  GIT_WORK_TREE_ENVIRONMENT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ chdir (char*) ; 
 scalar_t__ check_repository_format_gently (char*,struct repository_format*,int*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ) ; 
 scalar_t__ getenv (int /*<<< orphan*/ ) ; 
 scalar_t__ git_work_tree_cfg ; 
 int inside_git_dir ; 
 scalar_t__ inside_work_tree ; 
 int offset_1st_component (char*) ; 
 int /*<<< orphan*/  set_git_dir (char*) ; 
 int /*<<< orphan*/  setenv (int /*<<< orphan*/ ,char*,int) ; 
 char const* setup_explicit_git_dir (char const*,struct strbuf*,struct repository_format*,int*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 char* xmemdupz (char*,int) ; 

__attribute__((used)) static const char *setup_bare_git_dir(struct strbuf *cwd, int offset,
				      struct repository_format *repo_fmt,
				      int *nongit_ok)
{
	int root_len;

	if (check_repository_format_gently(".", repo_fmt, nongit_ok))
		return NULL;

	setenv(GIT_IMPLICIT_WORK_TREE_ENVIRONMENT, "0", 1);

	/* --work-tree is set without --git-dir; use discovered one */
	if (getenv(GIT_WORK_TREE_ENVIRONMENT) || git_work_tree_cfg) {
		static const char *gitdir;

		gitdir = offset == cwd->len ? "." : xmemdupz(cwd->buf, offset);
		if (chdir(cwd->buf))
			die_errno(_("cannot come back to cwd"));
		return setup_explicit_git_dir(gitdir, cwd, repo_fmt, nongit_ok);
	}

	inside_git_dir = 1;
	inside_work_tree = 0;
	if (offset != cwd->len) {
		if (chdir(cwd->buf))
			die_errno(_("cannot come back to cwd"));
		root_len = offset_1st_component(cwd->buf);
		strbuf_setlen(cwd, offset > root_len ? offset : root_len);
		set_git_dir(cwd->buf);
	}
	else
		set_git_dir(".");
	return NULL;
}