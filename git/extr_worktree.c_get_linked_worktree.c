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
struct worktree {int /*<<< orphan*/  id; int /*<<< orphan*/  path; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  add_head_info (struct worktree*) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  get_git_common_dir () ; 
 int /*<<< orphan*/  strbuf_add_absolute_path (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_git_common_path (struct strbuf*,int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ strbuf_read_file (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_rtrim (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_strip_suffix (struct strbuf*,char*) ; 
 int /*<<< orphan*/  the_repository ; 
 struct worktree* xcalloc (int,int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static struct worktree *get_linked_worktree(const char *id)
{
	struct worktree *worktree = NULL;
	struct strbuf path = STRBUF_INIT;
	struct strbuf worktree_path = STRBUF_INIT;

	if (!id)
		die("Missing linked worktree name");

	strbuf_git_common_path(&path, the_repository, "worktrees/%s/gitdir", id);
	if (strbuf_read_file(&worktree_path, path.buf, 0) <= 0)
		/* invalid gitdir file */
		goto done;

	strbuf_rtrim(&worktree_path);
	if (!strbuf_strip_suffix(&worktree_path, "/.git")) {
		strbuf_reset(&worktree_path);
		strbuf_add_absolute_path(&worktree_path, ".");
		strbuf_strip_suffix(&worktree_path, "/.");
	}

	strbuf_reset(&path);
	strbuf_addf(&path, "%s/worktrees/%s/HEAD", get_git_common_dir(), id);

	worktree = xcalloc(1, sizeof(*worktree));
	worktree->path = strbuf_detach(&worktree_path, NULL);
	worktree->id = xstrdup(id);
	add_head_info(worktree);

done:
	strbuf_release(&path);
	strbuf_release(&worktree_path);
	return worktree;
}