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
struct option {int dummy; } ;

/* Variables and functions */
 struct option OPT_END () ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 struct worktree* find_worktree (struct worktree**,char const*,char const*) ; 
 int /*<<< orphan*/  free_worktrees (struct worktree**) ; 
 struct worktree** get_worktrees (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_common_path (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_main_worktree (struct worktree*) ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int unlink_or_warn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 
 int /*<<< orphan*/  worktree_lock_reason (struct worktree*) ; 
 int /*<<< orphan*/  worktree_usage ; 

__attribute__((used)) static int unlock_worktree(int ac, const char **av, const char *prefix)
{
	struct option options[] = {
		OPT_END()
	};
	struct worktree **worktrees, *wt;
	int ret;

	ac = parse_options(ac, av, prefix, options, worktree_usage, 0);
	if (ac != 1)
		usage_with_options(worktree_usage, options);

	worktrees = get_worktrees(0);
	wt = find_worktree(worktrees, prefix, av[0]);
	if (!wt)
		die(_("'%s' is not a working tree"), av[0]);
	if (is_main_worktree(wt))
		die(_("The main working tree cannot be locked or unlocked"));
	if (!worktree_lock_reason(wt))
		die(_("'%s' is not locked"), av[0]);
	ret = unlink_or_warn(git_common_path("worktrees/%s/locked", wt->id));
	free_worktrees(worktrees);
	return ret;
}