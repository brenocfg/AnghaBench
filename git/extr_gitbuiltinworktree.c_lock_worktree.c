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
 int /*<<< orphan*/  N_ (char*) ; 
 struct option OPT_END () ; 
 struct option OPT_STRING (int /*<<< orphan*/ ,char*,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 struct worktree* find_worktree (struct worktree**,char const*,char const*) ; 
 int /*<<< orphan*/  free_worktrees (struct worktree**) ; 
 struct worktree** get_worktrees (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_common_path (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_main_worktree (struct worktree*) ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 
 char* worktree_lock_reason (struct worktree*) ; 
 int /*<<< orphan*/  worktree_usage ; 
 int /*<<< orphan*/  write_file (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int lock_worktree(int ac, const char **av, const char *prefix)
{
	const char *reason = "", *old_reason;
	struct option options[] = {
		OPT_STRING(0, "reason", &reason, N_("string"),
			   N_("reason for locking")),
		OPT_END()
	};
	struct worktree **worktrees, *wt;

	ac = parse_options(ac, av, prefix, options, worktree_usage, 0);
	if (ac != 1)
		usage_with_options(worktree_usage, options);

	worktrees = get_worktrees(0);
	wt = find_worktree(worktrees, prefix, av[0]);
	if (!wt)
		die(_("'%s' is not a working tree"), av[0]);
	if (is_main_worktree(wt))
		die(_("The main working tree cannot be locked or unlocked"));

	old_reason = worktree_lock_reason(wt);
	if (old_reason) {
		if (*old_reason)
			die(_("'%s' is already locked, reason: %s"),
			    av[0], old_reason);
		die(_("'%s' is already locked"), av[0]);
	}

	write_file(git_common_path("worktrees/%s/locked", wt->id),
		   "%s", reason);
	free_worktrees(worktrees);
	return 0;
}