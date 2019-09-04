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
struct checkout_opts {int /*<<< orphan*/  pathspec; scalar_t__ source_tree; int /*<<< orphan*/  ignore_skipworktree; } ;
struct cache_entry {int ce_flags; } ;

/* Variables and functions */
 int CE_MATCHED ; 
 int CE_UPDATE ; 
 scalar_t__ ce_path_match (int /*<<< orphan*/ *,struct cache_entry*,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ce_skip_worktree (struct cache_entry*) ; 
 int /*<<< orphan*/  the_index ; 

__attribute__((used)) static void mark_ce_for_checkout_overlay(struct cache_entry *ce,
					 char *ps_matched,
					 const struct checkout_opts *opts)
{
	ce->ce_flags &= ~CE_MATCHED;
	if (!opts->ignore_skipworktree && ce_skip_worktree(ce))
		return;
	if (opts->source_tree && !(ce->ce_flags & CE_UPDATE))
		/*
		 * "git checkout tree-ish -- path", but this entry
		 * is in the original index but is not in tree-ish
		 * or does not match the pathspec; it will not be
		 * checked out to the working tree.  We will not do
		 * anything to this entry at all.
		 */
		return;
	/*
	 * Either this entry came from the tree-ish we are
	 * checking the paths out of, or we are checking out
	 * of the index.
	 *
	 * If it comes from the tree-ish, we already know it
	 * matches the pathspec and could just stamp
	 * CE_MATCHED to it from update_some(). But we still
	 * need ps_matched and read_tree_recursive (and
	 * eventually tree_entry_interesting) cannot fill
	 * ps_matched yet. Once it can, we can avoid calling
	 * match_pathspec() for _all_ entries when
	 * opts->source_tree != NULL.
	 */
	if (ce_path_match(&the_index, ce, &opts->pathspec, ps_matched))
		ce->ce_flags |= CE_MATCHED;
}