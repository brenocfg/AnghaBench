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
struct checkout_opts {scalar_t__ source_tree; int /*<<< orphan*/  pathspec; int /*<<< orphan*/  ignore_skipworktree; } ;
struct cache_entry {int ce_flags; } ;

/* Variables and functions */
 int CE_MATCHED ; 
 int CE_REMOVE ; 
 int CE_UPDATE ; 
 int CE_WT_REMOVE ; 
 scalar_t__ ce_path_match (int /*<<< orphan*/ *,struct cache_entry*,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ce_skip_worktree (struct cache_entry*) ; 
 int /*<<< orphan*/  the_index ; 

__attribute__((used)) static void mark_ce_for_checkout_no_overlay(struct cache_entry *ce,
					    char *ps_matched,
					    const struct checkout_opts *opts)
{
	ce->ce_flags &= ~CE_MATCHED;
	if (!opts->ignore_skipworktree && ce_skip_worktree(ce))
		return;
	if (ce_path_match(&the_index, ce, &opts->pathspec, ps_matched)) {
		ce->ce_flags |= CE_MATCHED;
		if (opts->source_tree && !(ce->ce_flags & CE_UPDATE))
			/*
			 * In overlay mode, but the path is not in
			 * tree-ish, which means we should remove it
			 * from the index and the working tree.
			 */
			ce->ce_flags |= CE_REMOVE | CE_WT_REMOVE;
	}
}