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
struct worktree {int /*<<< orphan*/  path; scalar_t__ is_current; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 struct worktree* find_shared_symref (char*,char const*) ; 
 int /*<<< orphan*/  skip_prefix (char const*,char*,char const**) ; 

void die_if_checked_out(const char *branch, int ignore_current_worktree)
{
	const struct worktree *wt;

	wt = find_shared_symref("HEAD", branch);
	if (!wt || (ignore_current_worktree && wt->is_current))
		return;
	skip_prefix(branch, "refs/heads/", &branch);
	die(_("'%s' is already checked out at '%s'"),
	    branch, wt->path);
}