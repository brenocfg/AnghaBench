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
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  connect_wt_gitdir_in_nested (char*,char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  git_config_set_in_file (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* real_pathdup (char const*,int) ; 
 int /*<<< orphan*/  relative_path (char*,char*,struct strbuf*) ; 
 scalar_t__ safe_create_leading_directories_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  write_file (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void connect_work_tree_and_git_dir(const char *work_tree_,
				   const char *git_dir_,
				   int recurse_into_nested)
{
	struct strbuf gitfile_sb = STRBUF_INIT;
	struct strbuf cfg_sb = STRBUF_INIT;
	struct strbuf rel_path = STRBUF_INIT;
	char *git_dir, *work_tree;

	/* Prepare .git file */
	strbuf_addf(&gitfile_sb, "%s/.git", work_tree_);
	if (safe_create_leading_directories_const(gitfile_sb.buf))
		die(_("could not create directories for %s"), gitfile_sb.buf);

	/* Prepare config file */
	strbuf_addf(&cfg_sb, "%s/config", git_dir_);
	if (safe_create_leading_directories_const(cfg_sb.buf))
		die(_("could not create directories for %s"), cfg_sb.buf);

	git_dir = real_pathdup(git_dir_, 1);
	work_tree = real_pathdup(work_tree_, 1);

	/* Write .git file */
	write_file(gitfile_sb.buf, "gitdir: %s",
		   relative_path(git_dir, work_tree, &rel_path));
	/* Update core.worktree setting */
	git_config_set_in_file(cfg_sb.buf, "core.worktree",
			       relative_path(work_tree, git_dir, &rel_path));

	strbuf_release(&gitfile_sb);
	strbuf_release(&cfg_sb);
	strbuf_release(&rel_path);

	if (recurse_into_nested)
		connect_wt_gitdir_in_nested(work_tree, git_dir);

	free(work_tree);
	free(git_dir);
}