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
struct worktree {int /*<<< orphan*/  id; } ;
struct strbuf {int dummy; } ;
struct repository {int /*<<< orphan*/  commondir; int /*<<< orphan*/  gitdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_git_common_path (struct strbuf*,struct repository const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void strbuf_worktree_gitdir(struct strbuf *buf,
				   const struct repository *repo,
				   const struct worktree *wt)
{
	if (!wt)
		strbuf_addstr(buf, repo->gitdir);
	else if (!wt->id)
		strbuf_addstr(buf, repo->commondir);
	else
		strbuf_git_common_path(buf, repo, "worktrees/%s", wt->id);
}