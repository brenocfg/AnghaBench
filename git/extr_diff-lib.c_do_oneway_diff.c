#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct unpack_trees_options {scalar_t__ index_only; struct rev_info* unpack_data; } ;
struct TYPE_2__ {scalar_t__ ita_invisible_in_index; } ;
struct rev_info {TYPE_1__ diffopt; int /*<<< orphan*/  ignore_merges; } ;
struct diff_filepair {int /*<<< orphan*/  one; } ;
struct cache_entry {int ce_flags; int /*<<< orphan*/  ce_mode; int /*<<< orphan*/  oid; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CE_VALID ; 
 scalar_t__ ce_intent_to_add (struct cache_entry const*) ; 
 scalar_t__ ce_skip_worktree (struct cache_entry const*) ; 
 scalar_t__ ce_stage (struct cache_entry const*) ; 
 int /*<<< orphan*/  diff_index_show_file (struct rev_info*,char*,struct cache_entry const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct diff_filepair* diff_unmerge (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_filespec (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_modified (struct rev_info*,struct cache_entry const*,struct cache_entry const*,int,int,int) ; 
 int /*<<< orphan*/  show_new_file (struct rev_info*,struct cache_entry const*,int,int) ; 

__attribute__((used)) static void do_oneway_diff(struct unpack_trees_options *o,
			   const struct cache_entry *idx,
			   const struct cache_entry *tree)
{
	struct rev_info *revs = o->unpack_data;
	int match_missing, cached;

	/*
	 * i-t-a entries do not actually exist in the index (if we're
	 * looking at its content)
	 */
	if (o->index_only &&
	    revs->diffopt.ita_invisible_in_index &&
	    idx && ce_intent_to_add(idx)) {
		idx = NULL;
		if (!tree)
			return;	/* nothing to diff.. */
	}

	/* if the entry is not checked out, don't examine work tree */
	cached = o->index_only ||
		(idx && ((idx->ce_flags & CE_VALID) || ce_skip_worktree(idx)));
	/*
	 * Backward compatibility wart - "diff-index -m" does
	 * not mean "do not ignore merges", but "match_missing".
	 *
	 * But with the revision flag parsing, that's found in
	 * "!revs->ignore_merges".
	 */
	match_missing = !revs->ignore_merges;

	if (cached && idx && ce_stage(idx)) {
		struct diff_filepair *pair;
		pair = diff_unmerge(&revs->diffopt, idx->name);
		if (tree)
			fill_filespec(pair->one, &tree->oid, 1,
				      tree->ce_mode);
		return;
	}

	/*
	 * Something added to the tree?
	 */
	if (!tree) {
		show_new_file(revs, idx, cached, match_missing);
		return;
	}

	/*
	 * Something removed from the tree?
	 */
	if (!idx) {
		diff_index_show_file(revs, "-", tree, &tree->oid, 1,
				     tree->ce_mode, 0);
		return;
	}

	/* Show difference between old and new */
	show_modified(revs, tree, idx, 1, cached, match_missing);
}