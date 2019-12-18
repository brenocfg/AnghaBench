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
struct strbuf {char const* buf; } ;
struct option {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_ (char*) ; 
 struct option OPT_END () ; 
 struct option OPT__FORCE (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_OPT_NOCOMPLETE ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  WT_VALIDATE_WORKTREE_MISSING_OK ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  check_clean_worktree (struct worktree*,char const*) ; 
 int delete_git_dir (int /*<<< orphan*/ ) ; 
 int delete_git_work_tree (struct worktree*) ; 
 int /*<<< orphan*/  delete_worktrees_dir_if_empty () ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 scalar_t__ file_exists (int /*<<< orphan*/ ) ; 
 struct worktree* find_worktree (struct worktree**,char const*,char const*) ; 
 int /*<<< orphan*/  free_worktrees (struct worktree**) ; 
 struct worktree** get_worktrees (int /*<<< orphan*/ ) ; 
 scalar_t__ is_main_worktree (struct worktree*) ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 
 scalar_t__ validate_worktree (struct worktree*,struct strbuf*,int /*<<< orphan*/ ) ; 
 char* worktree_lock_reason (struct worktree*) ; 
 int /*<<< orphan*/  worktree_usage ; 

__attribute__((used)) static int remove_worktree(int ac, const char **av, const char *prefix)
{
	int force = 0;
	struct option options[] = {
		OPT__FORCE(&force,
			 N_("force removal even if worktree is dirty or locked"),
			 PARSE_OPT_NOCOMPLETE),
		OPT_END()
	};
	struct worktree **worktrees, *wt;
	struct strbuf errmsg = STRBUF_INIT;
	const char *reason = NULL;
	int ret = 0;

	ac = parse_options(ac, av, prefix, options, worktree_usage, 0);
	if (ac != 1)
		usage_with_options(worktree_usage, options);

	worktrees = get_worktrees(0);
	wt = find_worktree(worktrees, prefix, av[0]);
	if (!wt)
		die(_("'%s' is not a working tree"), av[0]);
	if (is_main_worktree(wt))
		die(_("'%s' is a main working tree"), av[0]);
	if (force < 2)
		reason = worktree_lock_reason(wt);
	if (reason) {
		if (*reason)
			die(_("cannot remove a locked working tree, lock reason: %s\nuse 'remove -f -f' to override or unlock first"),
			    reason);
		die(_("cannot remove a locked working tree;\nuse 'remove -f -f' to override or unlock first"));
	}
	if (validate_worktree(wt, &errmsg, WT_VALIDATE_WORKTREE_MISSING_OK))
		die(_("validation failed, cannot remove working tree: %s"),
		    errmsg.buf);
	strbuf_release(&errmsg);

	if (file_exists(wt->path)) {
		if (!force)
			check_clean_worktree(wt, av[0]);

		ret |= delete_git_work_tree(wt);
	}
	/*
	 * continue on even if ret is non-zero, there's no going back
	 * from here.
	 */
	ret |= delete_git_dir(wt->id);
	delete_worktrees_dir_if_empty();

	free_worktrees(worktrees);
	return ret;
}