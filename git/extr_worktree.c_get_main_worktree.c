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
struct worktree {int is_bare; int /*<<< orphan*/  path; } ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  add_head_info (struct worktree*) ; 
 int /*<<< orphan*/  get_git_common_dir () ; 
 scalar_t__ is_bare_repository () ; 
 int is_bare_repository_cfg ; 
 int /*<<< orphan*/  strbuf_add_absolute_path (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_strip_suffix (struct strbuf*,char*) ; 
 struct worktree* xcalloc (int,int) ; 

__attribute__((used)) static struct worktree *get_main_worktree(void)
{
	struct worktree *worktree = NULL;
	struct strbuf path = STRBUF_INIT;
	struct strbuf worktree_path = STRBUF_INIT;

	strbuf_add_absolute_path(&worktree_path, get_git_common_dir());
	if (!strbuf_strip_suffix(&worktree_path, "/.git"))
		strbuf_strip_suffix(&worktree_path, "/.");

	strbuf_addf(&path, "%s/HEAD", get_git_common_dir());

	worktree = xcalloc(1, sizeof(*worktree));
	worktree->path = strbuf_detach(&worktree_path, NULL);
	/*
	 * NEEDSWORK: If this function is called from a secondary worktree and
	 * config.worktree is present, is_bare_repository_cfg will reflect the
	 * contents of config.worktree, not the contents of the main worktree.
	 * This means that worktree->is_bare may be set to 0 even if the main
	 * worktree is configured to be bare.
	 */
	worktree->is_bare = (is_bare_repository_cfg == 1) ||
		is_bare_repository();
	add_head_info(worktree);

	strbuf_release(&path);
	strbuf_release(&worktree_path);
	return worktree;
}