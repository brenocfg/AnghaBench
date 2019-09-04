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
struct worktree {int /*<<< orphan*/  path; int /*<<< orphan*/  id; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ fspathcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_common_path (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_main_worktree (struct worktree*) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_realpath (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  write_file (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void update_worktree_location(struct worktree *wt, const char *path_)
{
	struct strbuf path = STRBUF_INIT;

	if (is_main_worktree(wt))
		BUG("can't relocate main worktree");

	strbuf_realpath(&path, path_, 1);
	if (fspathcmp(wt->path, path.buf)) {
		write_file(git_common_path("worktrees/%s/gitdir", wt->id),
			   "%s/.git", path.buf);
		free(wt->path);
		wt->path = strbuf_detach(&path, NULL);
	}
	strbuf_release(&path);
}