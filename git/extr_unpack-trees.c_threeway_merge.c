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
struct unpack_trees_options {int head_idx; int nontrivial_merge; struct cache_entry const* const df_conflict_entry; scalar_t__ aggressive; } ;
struct cache_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_WOULD_LOSE_UNTRACKED_REMOVED ; 
 int deleted_entry (struct cache_entry const*,struct cache_entry const*,struct unpack_trees_options*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ keep_entry (struct cache_entry const*,struct unpack_trees_options*) ; 
 int merged_entry (struct cache_entry const*,struct cache_entry const*,struct unpack_trees_options*) ; 
 int reject_merge (struct cache_entry const*,struct unpack_trees_options*) ; 
 scalar_t__ same (struct cache_entry const*,struct cache_entry const*) ; 
 int /*<<< orphan*/  show_stage_entry (int /*<<< orphan*/ ,char*,struct cache_entry const* const) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verify_absent (struct cache_entry const*,int /*<<< orphan*/ ,struct unpack_trees_options*) ; 
 scalar_t__ verify_uptodate (struct cache_entry const*,struct unpack_trees_options*) ; 

int threeway_merge(const struct cache_entry * const *stages,
		   struct unpack_trees_options *o)
{
	const struct cache_entry *index;
	const struct cache_entry *head;
	const struct cache_entry *remote = stages[o->head_idx + 1];
	int count;
	int head_match = 0;
	int remote_match = 0;

	int df_conflict_head = 0;
	int df_conflict_remote = 0;

	int any_anc_missing = 0;
	int no_anc_exists = 1;
	int i;

	for (i = 1; i < o->head_idx; i++) {
		if (!stages[i] || stages[i] == o->df_conflict_entry)
			any_anc_missing = 1;
		else
			no_anc_exists = 0;
	}

	index = stages[0];
	head = stages[o->head_idx];

	if (head == o->df_conflict_entry) {
		df_conflict_head = 1;
		head = NULL;
	}

	if (remote == o->df_conflict_entry) {
		df_conflict_remote = 1;
		remote = NULL;
	}

	/*
	 * First, if there's a #16 situation, note that to prevent #13
	 * and #14.
	 */
	if (!same(remote, head)) {
		for (i = 1; i < o->head_idx; i++) {
			if (same(stages[i], head)) {
				head_match = i;
			}
			if (same(stages[i], remote)) {
				remote_match = i;
			}
		}
	}

	/*
	 * We start with cases where the index is allowed to match
	 * something other than the head: #14(ALT) and #2ALT, where it
	 * is permitted to match the result instead.
	 */
	/* #14, #14ALT, #2ALT */
	if (remote && !df_conflict_head && head_match && !remote_match) {
		if (index && !same(index, remote) && !same(index, head))
			return reject_merge(index, o);
		return merged_entry(remote, index, o);
	}
	/*
	 * If we have an entry in the index cache, then we want to
	 * make sure that it matches head.
	 */
	if (index && !same(index, head))
		return reject_merge(index, o);

	if (head) {
		/* #5ALT, #15 */
		if (same(head, remote))
			return merged_entry(head, index, o);
		/* #13, #3ALT */
		if (!df_conflict_remote && remote_match && !head_match)
			return merged_entry(head, index, o);
	}

	/* #1 */
	if (!head && !remote && any_anc_missing)
		return 0;

	/*
	 * Under the "aggressive" rule, we resolve mostly trivial
	 * cases that we historically had git-merge-one-file resolve.
	 */
	if (o->aggressive) {
		int head_deleted = !head;
		int remote_deleted = !remote;
		const struct cache_entry *ce = NULL;

		if (index)
			ce = index;
		else if (head)
			ce = head;
		else if (remote)
			ce = remote;
		else {
			for (i = 1; i < o->head_idx; i++) {
				if (stages[i] && stages[i] != o->df_conflict_entry) {
					ce = stages[i];
					break;
				}
			}
		}

		/*
		 * Deleted in both.
		 * Deleted in one and unchanged in the other.
		 */
		if ((head_deleted && remote_deleted) ||
		    (head_deleted && remote && remote_match) ||
		    (remote_deleted && head && head_match)) {
			if (index)
				return deleted_entry(index, index, o);
			if (ce && !head_deleted) {
				if (verify_absent(ce, ERROR_WOULD_LOSE_UNTRACKED_REMOVED, o))
					return -1;
			}
			return 0;
		}
		/*
		 * Added in both, identically.
		 */
		if (no_anc_exists && head && remote && same(head, remote))
			return merged_entry(head, index, o);

	}

	/* Below are "no merge" cases, which require that the index be
	 * up-to-date to avoid the files getting overwritten with
	 * conflict resolution files.
	 */
	if (index) {
		if (verify_uptodate(index, o))
			return -1;
	}

	o->nontrivial_merge = 1;

	/* #2, #3, #4, #6, #7, #9, #10, #11. */
	count = 0;
	if (!head_match || !remote_match) {
		for (i = 1; i < o->head_idx; i++) {
			if (stages[i] && stages[i] != o->df_conflict_entry) {
				keep_entry(stages[i], o);
				count++;
				break;
			}
		}
	}
#if DBRT_DEBUG
	else {
		fprintf(stderr, "read-tree: warning #16 detected\n");
		show_stage_entry(stderr, "head   ", stages[head_match]);
		show_stage_entry(stderr, "remote ", stages[remote_match]);
	}
#endif
	if (head) { count += keep_entry(head, o); }
	if (remote) { count += keep_entry(remote, o); }
	return count;
}