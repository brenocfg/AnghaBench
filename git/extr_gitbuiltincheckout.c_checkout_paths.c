#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct object_id {int dummy; } ;
struct lock_file {int dummy; } ;
struct commit {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  nr; } ;
struct checkout_opts {scalar_t__ track; TYPE_4__* source_tree; scalar_t__ count_checkout_paths; scalar_t__ merge; scalar_t__ overlay_mode; scalar_t__ writeout_stage; scalar_t__ force; TYPE_2__ pathspec; scalar_t__ patch_mode; int /*<<< orphan*/  new_branch; scalar_t__ force_detach; scalar_t__ new_branch_log; } ;
struct checkout {int force; int refresh_cache; int /*<<< orphan*/ * istate; } ;
typedef  struct cache_entry {int ce_flags; int /*<<< orphan*/  name; } const cache_entry ;
struct TYPE_7__ {int /*<<< orphan*/  oid; } ;
struct TYPE_9__ {TYPE_1__ object; } ;

/* Variables and functions */
 scalar_t__ BRANCH_TRACK_UNSPECIFIED ; 
 int CE_MATCHED ; 
 struct checkout CHECKOUT_INIT ; 
 int /*<<< orphan*/  COMMIT_LOCK ; 
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
 int /*<<< orphan*/  LOCK_DIE_ON_ERROR ; 
 struct lock_file LOCK_INIT ; 
 int /*<<< orphan*/  Q_ (char*,char*,int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct cache_entry const** active_cache ; 
 int active_nr ; 
 int /*<<< orphan*/  ce_stage (struct cache_entry const*) ; 
 int check_stage (scalar_t__,struct cache_entry const*,int,scalar_t__) ; 
 int check_stages (int,struct cache_entry const*,int) ; 
 int checkout_entry (struct cache_entry const*,struct checkout*,int /*<<< orphan*/ *,int*) ; 
 int checkout_merged (int,struct checkout*,int*) ; 
 int checkout_stage (scalar_t__,struct cache_entry const*,int,struct checkout*,int*,scalar_t__) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  enable_delayed_checkout (struct checkout*) ; 
 int error (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  find_unique_abbrev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int finish_delayed_checkout (struct checkout*,int*) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct commit* lookup_commit_reference_gently (int /*<<< orphan*/ ,struct object_id*,int) ; 
 int /*<<< orphan*/  mark_ce_for_checkout_no_overlay (struct cache_entry const*,char*,struct checkout_opts const*) ; 
 int /*<<< orphan*/  mark_ce_for_checkout_overlay (struct cache_entry const*,char*,struct checkout_opts const*) ; 
 int post_checkout_hook (struct commit*,struct commit*,int /*<<< orphan*/ ) ; 
 scalar_t__ read_cache_preload (TYPE_2__*) ; 
 int /*<<< orphan*/  read_ref_full (char*,int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_tree_some (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  remove_marked_cache_entries (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  remove_scheduled_dirs () ; 
 int /*<<< orphan*/  repo_hold_locked_index (int /*<<< orphan*/ ,struct lock_file*,int /*<<< orphan*/ ) ; 
 scalar_t__ report_path_error (char*,TYPE_2__*) ; 
 int run_add_interactive (char const*,char*,TYPE_2__*) ; 
 int skip_same_name (struct cache_entry const*,int) ; 
 int /*<<< orphan*/  stderr ; 
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
	struct checkout state = CHECKOUT_INIT;
	static char *ps_matched;
	struct object_id rev;
	struct commit *head;
	int errs = 0;
	struct lock_file lock_file = LOCK_INIT;
	int nr_checkouts = 0, nr_unmerged = 0;

	trace2_cmd_mode(opts->patch_mode ? "patch" : "path");

	if (opts->track != BRANCH_TRACK_UNSPECIFIED)
		die(_("'%s' cannot be used with updating paths"), "--track");

	if (opts->new_branch_log)
		die(_("'%s' cannot be used with updating paths"), "-l");

	if (opts->force && opts->patch_mode)
		die(_("'%s' cannot be used with updating paths"), "-f");

	if (opts->force_detach)
		die(_("'%s' cannot be used with updating paths"), "--detach");

	if (opts->merge && opts->patch_mode)
		die(_("'%s' cannot be used with %s"), "--merge", "--patch");

	if (opts->force && opts->merge)
		die(_("'%s' cannot be used with %s"), "-f", "-m");

	if (opts->new_branch)
		die(_("Cannot update paths and switch to branch '%s' at the same time."),
		    opts->new_branch);

	if (opts->patch_mode)
		return run_add_interactive(revision, "--patch=checkout",
					   &opts->pathspec);

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
			if (opts->force) {
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
	state.force = 1;
	state.refresh_cache = 1;
	state.istate = &the_index;

	enable_delayed_checkout(&state);
	for (pos = 0; pos < active_nr; pos++) {
		struct cache_entry *ce = active_cache[pos];
		if (ce->ce_flags & CE_MATCHED) {
			if (!ce_stage(ce)) {
				errs |= checkout_entry(ce, &state,
						       NULL, &nr_checkouts);
				continue;
			}
			if (opts->writeout_stage)
				errs |= checkout_stage(opts->writeout_stage,
						       ce, pos,
						       &state,
						       &nr_checkouts, opts->overlay_mode);
			else if (opts->merge)
				errs |= checkout_merged(pos, &state,
							&nr_unmerged);
			pos = skip_same_name(ce, pos) - 1;
		}
	}
	remove_marked_cache_entries(&the_index, 1);
	remove_scheduled_dirs();
	errs |= finish_delayed_checkout(&state, &nr_checkouts);

	if (opts->count_checkout_paths) {
		if (nr_unmerged)
			fprintf_ln(stderr, Q_("Recreated %d merge conflict",
					      "Recreated %d merge conflicts",
					      nr_unmerged),
				   nr_unmerged);
		if (opts->source_tree)
			fprintf_ln(stderr, Q_("Updated %d path from %s",
					      "Updated %d paths from %s",
					      nr_checkouts),
				   nr_checkouts,
				   find_unique_abbrev(&opts->source_tree->object.oid,
						      DEFAULT_ABBREV));
		else if (!nr_unmerged || nr_checkouts)
			fprintf_ln(stderr, Q_("Updated %d path from the index",
					      "Updated %d paths from the index",
					      nr_checkouts),
				   nr_checkouts);
	}

	if (write_locked_index(&the_index, &lock_file, COMMIT_LOCK))
		die(_("unable to write new index file"));

	read_ref_full("HEAD", 0, &rev, NULL);
	head = lookup_commit_reference_gently(the_repository, &rev, 1);

	errs |= post_checkout_hook(head, head, 0);
	return errs;
}