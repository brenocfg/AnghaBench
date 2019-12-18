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
struct stat {int dummy; } ;
struct index_state {int dummy; } ;
struct cache_entry {int ce_flags; scalar_t__ ce_namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  ce_mode; } ;

/* Variables and functions */
 int CE_FSMONITOR_VALID ; 
 unsigned int CE_MATCH_IGNORE_FSMONITOR ; 
 unsigned int CE_MATCH_IGNORE_MISSING ; 
 unsigned int CE_MATCH_IGNORE_SKIP_WORKTREE ; 
 unsigned int CE_MATCH_IGNORE_VALID ; 
 unsigned int CE_MATCH_REFRESH ; 
 int CE_VALID ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  S_ISGITLINK (int /*<<< orphan*/ ) ; 
 scalar_t__ assume_unchanged ; 
 int /*<<< orphan*/  ce_mark_uptodate (struct cache_entry*) ; 
 int /*<<< orphan*/  ce_namelen (struct cache_entry*) ; 
 scalar_t__ ce_skip_worktree (struct cache_entry*) ; 
 scalar_t__ ce_uptodate (struct cache_entry*) ; 
 int /*<<< orphan*/  copy_cache_entry (struct cache_entry*,struct cache_entry*) ; 
 int errno ; 
 int /*<<< orphan*/  fill_stat_cache_info (struct index_state*,struct cache_entry*,struct stat*) ; 
 scalar_t__ has_symlink_leading_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ie_match_stat (struct index_state*,struct cache_entry*,struct stat*,unsigned int) ; 
 scalar_t__ ie_modified (struct index_state*,struct cache_entry*,struct stat*,unsigned int) ; 
 scalar_t__ lstat (int /*<<< orphan*/ ,struct stat*) ; 
 struct cache_entry* make_empty_cache_entry (struct index_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_fsmonitor_valid (struct index_state*,struct cache_entry*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  refresh_fsmonitor (struct index_state*) ; 

__attribute__((used)) static struct cache_entry *refresh_cache_ent(struct index_state *istate,
					     struct cache_entry *ce,
					     unsigned int options, int *err,
					     int *changed_ret)
{
	struct stat st;
	struct cache_entry *updated;
	int changed;
	int refresh = options & CE_MATCH_REFRESH;
	int ignore_valid = options & CE_MATCH_IGNORE_VALID;
	int ignore_skip_worktree = options & CE_MATCH_IGNORE_SKIP_WORKTREE;
	int ignore_missing = options & CE_MATCH_IGNORE_MISSING;
	int ignore_fsmonitor = options & CE_MATCH_IGNORE_FSMONITOR;

	if (!refresh || ce_uptodate(ce))
		return ce;

	if (!ignore_fsmonitor)
		refresh_fsmonitor(istate);
	/*
	 * CE_VALID or CE_SKIP_WORKTREE means the user promised us
	 * that the change to the work tree does not matter and told
	 * us not to worry.
	 */
	if (!ignore_skip_worktree && ce_skip_worktree(ce)) {
		ce_mark_uptodate(ce);
		return ce;
	}
	if (!ignore_valid && (ce->ce_flags & CE_VALID)) {
		ce_mark_uptodate(ce);
		return ce;
	}
	if (!ignore_fsmonitor && (ce->ce_flags & CE_FSMONITOR_VALID)) {
		ce_mark_uptodate(ce);
		return ce;
	}

	if (has_symlink_leading_path(ce->name, ce_namelen(ce))) {
		if (ignore_missing)
			return ce;
		if (err)
			*err = ENOENT;
		return NULL;
	}

	if (lstat(ce->name, &st) < 0) {
		if (ignore_missing && errno == ENOENT)
			return ce;
		if (err)
			*err = errno;
		return NULL;
	}

	changed = ie_match_stat(istate, ce, &st, options);
	if (changed_ret)
		*changed_ret = changed;
	if (!changed) {
		/*
		 * The path is unchanged.  If we were told to ignore
		 * valid bit, then we did the actual stat check and
		 * found that the entry is unmodified.  If the entry
		 * is not marked VALID, this is the place to mark it
		 * valid again, under "assume unchanged" mode.
		 */
		if (ignore_valid && assume_unchanged &&
		    !(ce->ce_flags & CE_VALID))
			; /* mark this one VALID again */
		else {
			/*
			 * We do not mark the index itself "modified"
			 * because CE_UPTODATE flag is in-core only;
			 * we are not going to write this change out.
			 */
			if (!S_ISGITLINK(ce->ce_mode)) {
				ce_mark_uptodate(ce);
				mark_fsmonitor_valid(istate, ce);
			}
			return ce;
		}
	}

	if (ie_modified(istate, ce, &st, options)) {
		if (err)
			*err = EINVAL;
		return NULL;
	}

	updated = make_empty_cache_entry(istate, ce_namelen(ce));
	copy_cache_entry(updated, ce);
	memcpy(updated->name, ce->name, ce->ce_namelen + 1);
	fill_stat_cache_info(istate, updated, &st);
	/*
	 * If ignore_valid is not set, we should leave CE_VALID bit
	 * alone.  Otherwise, paths marked with --no-assume-unchanged
	 * (i.e. things to be edited) will reacquire CE_VALID bit
	 * automatically, which is not really what we want.
	 */
	if (!ignore_valid && assume_unchanged &&
	    !(ce->ce_flags & CE_VALID))
		updated->ce_flags &= ~CE_VALID;

	/* istate->cache_changed is updated in the caller */
	return updated;
}