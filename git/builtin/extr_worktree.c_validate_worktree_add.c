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
struct add_opts {int force; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ delete_git_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ file_exists (char const*) ; 
 struct worktree* find_worktree (struct worktree**,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  free_worktrees (struct worktree**) ; 
 struct worktree** get_worktrees (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_empty_dir (char const*) ; 
 int /*<<< orphan*/  worktree_lock_reason (struct worktree*) ; 

__attribute__((used)) static void validate_worktree_add(const char *path, const struct add_opts *opts)
{
	struct worktree **worktrees;
	struct worktree *wt;
	int locked;

	if (file_exists(path) && !is_empty_dir(path))
		die(_("'%s' already exists"), path);

	worktrees = get_worktrees(0);
	/*
	 * find_worktree()'s suffix matching may undesirably find the main
	 * rather than a linked worktree (for instance, when the basenames
	 * of the main worktree and the one being created are the same).
	 * We're only interested in linked worktrees, so skip the main
	 * worktree with +1.
	 */
	wt = find_worktree(worktrees + 1, NULL, path);
	if (!wt)
		goto done;

	locked = !!worktree_lock_reason(wt);
	if ((!locked && opts->force) || (locked && opts->force > 1)) {
		if (delete_git_dir(wt->id))
		    die(_("unable to re-add worktree '%s'"), path);
		goto done;
	}

	if (locked)
		die(_("'%s' is a missing but locked worktree;\nuse 'add -f -f' to override, or 'unlock' and 'prune' or 'remove' to clear"), path);
	else
		die(_("'%s' is a missing but already registered worktree;\nuse 'add -f' to override, or 'prune' or 'remove' to clear"), path);

done:
	free_worktrees(worktrees);
}