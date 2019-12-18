#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct object_id {int dummy; } ;
struct lock_file {int dummy; } ;
struct commit {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  nr; } ;
struct checkout_opts {scalar_t__ track; int checkout_index; scalar_t__ source_tree; scalar_t__ checkout_worktree; scalar_t__ merge; scalar_t__ overlay_mode; scalar_t__ writeout_stage; int /*<<< orphan*/  quiet; scalar_t__ ignore_unmerged; TYPE_1__ pathspec; scalar_t__ patch_mode; int /*<<< orphan*/  from_treeish; int /*<<< orphan*/  new_branch; int /*<<< orphan*/  ignore_unmerged_opt; scalar_t__ force_detach; scalar_t__ new_branch_log; } ;
struct cache_entry {int ce_flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ BRANCH_TRACK_UNSPECIFIED ; 
 int /*<<< orphan*/  BUG (char*,scalar_t__,int) ; 
 int CE_MATCHED ; 
 int /*<<< orphan*/  COMMIT_LOCK ; 
 int /*<<< orphan*/  LOCK_DIE_ON_ERROR ; 
 struct lock_file LOCK_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct cache_entry** active_cache ; 
 int active_nr ; 
 int /*<<< orphan*/  ce_stage (struct cache_entry const*) ; 
 int check_stage (scalar_t__,struct cache_entry const*,int,scalar_t__) ; 
 int check_stages (int,struct cache_entry const*,int) ; 
 int checkout_worktree (struct checkout_opts const*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 int error (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct commit* lookup_commit_reference_gently (int /*<<< orphan*/ ,struct object_id*,int) ; 
 int /*<<< orphan*/  mark_ce_for_checkout_no_overlay (struct cache_entry*,char*,struct checkout_opts const*) ; 
 int /*<<< orphan*/  mark_ce_for_checkout_overlay (struct cache_entry*,char*,struct checkout_opts const*) ; 
 int post_checkout_hook (struct commit*,struct commit*,int /*<<< orphan*/ ) ; 
 scalar_t__ read_cache_preload (TYPE_1__*) ; 
 int /*<<< orphan*/  read_ref_full (char*,int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_tree_some (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  repo_hold_locked_index (int /*<<< orphan*/ ,struct lock_file*,int /*<<< orphan*/ ) ; 
 scalar_t__ report_path_error (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  rollback_lock_file (struct lock_file*) ; 
 int run_add_interactive (char const*,char const*,TYPE_1__*) ; 
 int skip_same_name (struct cache_entry const*,int) ; 
 int /*<<< orphan*/  the_index ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  trace2_cmd_mode (char*) ; 
 int /*<<< orphan*/  unmerge_marked_index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ write_locked_index (int /*<<< orphan*/ *,struct lock_file*,int /*<<< orphan*/ ) ; 
 char* xcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int checkout_paths(const struct checkout_opts *opts,
			  const char *revision)
{
	int pos;
	static char *ps_matched;
	struct object_id rev;
	struct commit *head;
	int errs = 0;
	struct lock_file lock_file = LOCK_INIT;
	int checkout_index;

	trace2_cmd_mode(opts->patch_mode ? "patch" : "path");

	if (opts->track != BRANCH_TRACK_UNSPECIFIED)
		die(_("'%s' cannot be used with updating paths"), "--track");

	if (opts->new_branch_log)
		die(_("'%s' cannot be used with updating paths"), "-l");

	if (opts->ignore_unmerged && opts->patch_mode)
		die(_("'%s' cannot be used with updating paths"),
		    opts->ignore_unmerged_opt);

	if (opts->force_detach)
		die(_("'%s' cannot be used with updating paths"), "--detach");

	if (opts->merge && opts->patch_mode)
		die(_("'%s' cannot be used with %s"), "--merge", "--patch");

	if (opts->ignore_unmerged && opts->merge)
		die(_("'%s' cannot be used with %s"),
		    opts->ignore_unmerged_opt, "-m");

	if (opts->new_branch)
		die(_("Cannot update paths and switch to branch '%s' at the same time."),
		    opts->new_branch);

	if (!opts->checkout_worktree && !opts->checkout_index)
		die(_("neither '%s' or '%s' is specified"),
		    "--staged", "--worktree");

	if (!opts->checkout_worktree && !opts->from_treeish)
		die(_("'%s' must be used when '%s' is not specified"),
		    "--worktree", "--source");

	if (opts->checkout_index && !opts->checkout_worktree &&
	    opts->writeout_stage)
		die(_("'%s' or '%s' cannot be used with %s"),
		    "--ours", "--theirs", "--staged");

	if (opts->checkout_index && !opts->checkout_worktree &&
	    opts->merge)
		die(_("'%s' or '%s' cannot be used with %s"),
		    "--merge", "--conflict", "--staged");

	if (opts->patch_mode) {
		const char *patch_mode;

		if (opts->checkout_index && opts->checkout_worktree)
			patch_mode = "--patch=checkout";
		else if (opts->checkout_index && !opts->checkout_worktree)
			patch_mode = "--patch=reset";
		else if (!opts->checkout_index && opts->checkout_worktree)
			patch_mode = "--patch=worktree";
		else
			BUG("either flag must have been set, worktree=%d, index=%d",
			    opts->checkout_worktree, opts->checkout_index);
		return run_add_interactive(revision, patch_mode, &opts->pathspec);
	}

	repo_hold_locked_index(the_repository, &lock_file, LOCK_DIE_ON_ERROR);
	if (read_cache_preload(&opts->pathspec) < 0)
		return error(_("index file corrupt"));

	if (opts->source_tree)
		read_tree_some(opts->source_tree, &opts->pathspec);

	ps_matched = xcalloc(opts->pathspec.nr, 1);

	/*
	 * Make sure all pathspecs participated in locating the paths
	 * to be checked out.
	 */
	for (pos = 0; pos < active_nr; pos++)
		if (opts->overlay_mode)
			mark_ce_for_checkout_overlay(active_cache[pos],
						     ps_matched,
						     opts);
		else
			mark_ce_for_checkout_no_overlay(active_cache[pos],
							ps_matched,
							opts);

	if (report_path_error(ps_matched, &opts->pathspec)) {
		free(ps_matched);
		return 1;
	}
	free(ps_matched);

	/* "checkout -m path" to recreate conflicted state */
	if (opts->merge)
		unmerge_marked_index(&the_index);

	/* Any unmerged paths? */
	for (pos = 0; pos < active_nr; pos++) {
		const struct cache_entry *ce = active_cache[pos];
		if (ce->ce_flags & CE_MATCHED) {
			if (!ce_stage(ce))
				continue;
			if (opts->ignore_unmerged) {
				if (!opts->quiet)
					warning(_("path '%s' is unmerged"), ce->name);
			} else if (opts->writeout_stage) {
				errs |= check_stage(opts->writeout_stage, ce, pos, opts->overlay_mode);
			} else if (opts->merge) {
				errs |= check_stages((1<<2) | (1<<3), ce, pos);
			} else {
				errs = 1;
				error(_("path '%s' is unmerged"), ce->name);
			}
			pos = skip_same_name(ce, pos) - 1;
		}
	}
	if (errs)
		return 1;

	/* Now we are committed to check them out */
	if (opts->checkout_worktree)
		errs |= checkout_worktree(opts);

	/*
	 * Allow updating the index when checking out from the index.
	 * This is to save new stat info.
	 */
	if (opts->checkout_worktree && !opts->checkout_index && !opts->source_tree)
		checkout_index = 1;
	else
		checkout_index = opts->checkout_index;

	if (checkout_index) {
		if (write_locked_index(&the_index, &lock_file, COMMIT_LOCK))
			die(_("unable to write new index file"));
	} else {
		/*
		 * NEEDSWORK: if --worktree is not specified, we
		 * should save stat info of checked out files in the
		 * index to avoid the next (potentially costly)
		 * refresh. But it's a bit tricker to do...
		 */
		rollback_lock_file(&lock_file);
	}

	read_ref_full("HEAD", 0, &rev, NULL);
	head = lookup_commit_reference_gently(the_repository, &rev, 1);

	errs |= post_checkout_hook(head, head, 0);
	return errs;
}