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
struct progress {int dummy; } ;
struct pathspec {int dummy; } ;
struct index_state {int cache_nr; int /*<<< orphan*/  cache_changed; struct cache_entry** cache; } ;
struct cache_entry {int /*<<< orphan*/  name; int /*<<< orphan*/  ce_flags; int /*<<< orphan*/  ce_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE_ENTRY_CHANGED ; 
 unsigned int CE_MATCH_IGNORE_MISSING ; 
 unsigned int CE_MATCH_IGNORE_VALID ; 
 unsigned int CE_MATCH_REFRESH ; 
 int /*<<< orphan*/  CE_UPDATE_IN_BASE ; 
 int /*<<< orphan*/  CE_VALID ; 
 int EINVAL ; 
 int ENOENT ; 
 unsigned int REFRESH_IGNORE_MISSING ; 
 unsigned int REFRESH_IGNORE_SUBMODULES ; 
 unsigned int REFRESH_IN_PORCELAIN ; 
 unsigned int REFRESH_PROGRESS ; 
 unsigned int REFRESH_QUIET ; 
 unsigned int REFRESH_REALLY ; 
 unsigned int REFRESH_UNMERGED ; 
 scalar_t__ S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int TYPE_CHANGED ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ ce_intent_to_add (struct cache_entry*) ; 
 int /*<<< orphan*/  ce_path_match (struct index_state*,struct cache_entry*,struct pathspec const*,char*) ; 
 scalar_t__ ce_stage (struct cache_entry*) ; 
 int /*<<< orphan*/  display_progress (struct progress*,int) ; 
 scalar_t__ isatty (int) ; 
 int /*<<< orphan*/  mark_fsmonitor_invalid (struct index_state*,struct cache_entry*) ; 
 int /*<<< orphan*/  preload_index (struct index_state*,struct pathspec const*,int /*<<< orphan*/ ) ; 
 struct cache_entry* refresh_cache_ent (struct index_state*,struct cache_entry*,unsigned int,int*,int*) ; 
 int /*<<< orphan*/  replace_index_entry (struct index_state*,int,struct cache_entry*) ; 
 int /*<<< orphan*/  show_file (char const*,int /*<<< orphan*/ ,int,int*,char const*) ; 
 struct progress* start_delayed_progress (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stop_progress (struct progress**) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_performance_enter () ; 
 int /*<<< orphan*/  trace_performance_leave (char*) ; 

int refresh_index(struct index_state *istate, unsigned int flags,
		  const struct pathspec *pathspec,
		  char *seen, const char *header_msg)
{
	int i;
	int has_errors = 0;
	int really = (flags & REFRESH_REALLY) != 0;
	int allow_unmerged = (flags & REFRESH_UNMERGED) != 0;
	int quiet = (flags & REFRESH_QUIET) != 0;
	int not_new = (flags & REFRESH_IGNORE_MISSING) != 0;
	int ignore_submodules = (flags & REFRESH_IGNORE_SUBMODULES) != 0;
	int first = 1;
	int in_porcelain = (flags & REFRESH_IN_PORCELAIN);
	unsigned int options = (CE_MATCH_REFRESH |
				(really ? CE_MATCH_IGNORE_VALID : 0) |
				(not_new ? CE_MATCH_IGNORE_MISSING : 0));
	const char *modified_fmt;
	const char *deleted_fmt;
	const char *typechange_fmt;
	const char *added_fmt;
	const char *unmerged_fmt;
	struct progress *progress = NULL;

	if (flags & REFRESH_PROGRESS && isatty(2))
		progress = start_delayed_progress(_("Refresh index"),
						  istate->cache_nr);

	trace_performance_enter();
	modified_fmt   = in_porcelain ? "M\t%s\n" : "%s: needs update\n";
	deleted_fmt    = in_porcelain ? "D\t%s\n" : "%s: needs update\n";
	typechange_fmt = in_porcelain ? "T\t%s\n" : "%s: needs update\n";
	added_fmt      = in_porcelain ? "A\t%s\n" : "%s: needs update\n";
	unmerged_fmt   = in_porcelain ? "U\t%s\n" : "%s: needs merge\n";
	/*
	 * Use the multi-threaded preload_index() to refresh most of the
	 * cache entries quickly then in the single threaded loop below,
	 * we only have to do the special cases that are left.
	 */
	preload_index(istate, pathspec, 0);
	for (i = 0; i < istate->cache_nr; i++) {
		struct cache_entry *ce, *new_entry;
		int cache_errno = 0;
		int changed = 0;
		int filtered = 0;

		ce = istate->cache[i];
		if (ignore_submodules && S_ISGITLINK(ce->ce_mode))
			continue;

		if (pathspec && !ce_path_match(istate, ce, pathspec, seen))
			filtered = 1;

		if (ce_stage(ce)) {
			while ((i < istate->cache_nr) &&
			       ! strcmp(istate->cache[i]->name, ce->name))
				i++;
			i--;
			if (allow_unmerged)
				continue;
			if (!filtered)
				show_file(unmerged_fmt, ce->name, in_porcelain,
					  &first, header_msg);
			has_errors = 1;
			continue;
		}

		if (filtered)
			continue;

		new_entry = refresh_cache_ent(istate, ce, options, &cache_errno, &changed);
		if (new_entry == ce)
			continue;
		if (progress)
			display_progress(progress, i);
		if (!new_entry) {
			const char *fmt;

			if (really && cache_errno == EINVAL) {
				/* If we are doing --really-refresh that
				 * means the index is not valid anymore.
				 */
				ce->ce_flags &= ~CE_VALID;
				ce->ce_flags |= CE_UPDATE_IN_BASE;
				mark_fsmonitor_invalid(istate, ce);
				istate->cache_changed |= CE_ENTRY_CHANGED;
			}
			if (quiet)
				continue;

			if (cache_errno == ENOENT)
				fmt = deleted_fmt;
			else if (ce_intent_to_add(ce))
				fmt = added_fmt; /* must be before other checks */
			else if (changed & TYPE_CHANGED)
				fmt = typechange_fmt;
			else
				fmt = modified_fmt;
			show_file(fmt,
				  ce->name, in_porcelain, &first, header_msg);
			has_errors = 1;
			continue;
		}

		replace_index_entry(istate, i, new_entry);
	}
	if (progress) {
		display_progress(progress, istate->cache_nr);
		stop_progress(&progress);
	}
	trace_performance_leave("refresh index");
	return has_errors;
}