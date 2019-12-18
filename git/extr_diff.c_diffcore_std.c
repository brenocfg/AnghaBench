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
struct oid_array {scalar_t__ nr; int /*<<< orphan*/  oid; } ;
struct diff_queue_struct {int nr; struct diff_filepair** queue; } ;
struct TYPE_2__ {int has_changes; int /*<<< orphan*/  diff_from_contents; } ;
struct diff_options {scalar_t__ repo; int break_opt; int pickaxe_opts; scalar_t__ found_follow; TYPE_1__ flags; scalar_t__ orderfile; scalar_t__ detect_rename; scalar_t__ skip_stat_unmatch; } ;
struct diff_filepair {int /*<<< orphan*/  two; int /*<<< orphan*/  one; } ;

/* Variables and functions */
 int DIFF_PICKAXE_KINDS_MASK ; 
 struct oid_array OID_ARRAY_INIT ; 
 int /*<<< orphan*/  add_if_missing (scalar_t__,struct oid_array*,int /*<<< orphan*/ ) ; 
 struct diff_queue_struct diff_queued_diff ; 
 int /*<<< orphan*/  diff_resolve_rename_copy () ; 
 int /*<<< orphan*/  diffcore_apply_filter (struct diff_options*) ; 
 int /*<<< orphan*/  diffcore_break (scalar_t__,int) ; 
 int /*<<< orphan*/  diffcore_merge_broken () ; 
 int /*<<< orphan*/  diffcore_order (scalar_t__) ; 
 int /*<<< orphan*/  diffcore_pickaxe (struct diff_options*) ; 
 int /*<<< orphan*/  diffcore_rename (struct diff_options*) ; 
 int /*<<< orphan*/  diffcore_skip_stat_unmatch (struct diff_options*) ; 
 scalar_t__ has_promisor_remote () ; 
 int /*<<< orphan*/  oid_array_clear (struct oid_array*) ; 
 int /*<<< orphan*/  promisor_remote_get_direct (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ the_repository ; 

void diffcore_std(struct diff_options *options)
{
	if (options->repo == the_repository && has_promisor_remote()) {
		/*
		 * Prefetch the diff pairs that are about to be flushed.
		 */
		int i;
		struct diff_queue_struct *q = &diff_queued_diff;
		struct oid_array to_fetch = OID_ARRAY_INIT;

		for (i = 0; i < q->nr; i++) {
			struct diff_filepair *p = q->queue[i];
			add_if_missing(options->repo, &to_fetch, p->one);
			add_if_missing(options->repo, &to_fetch, p->two);
		}
		if (to_fetch.nr)
			/*
			 * NEEDSWORK: Consider deduplicating the OIDs sent.
			 */
			promisor_remote_get_direct(options->repo,
						   to_fetch.oid, to_fetch.nr);
		oid_array_clear(&to_fetch);
	}

	/* NOTE please keep the following in sync with diff_tree_combined() */
	if (options->skip_stat_unmatch)
		diffcore_skip_stat_unmatch(options);
	if (!options->found_follow) {
		/* See try_to_follow_renames() in tree-diff.c */
		if (options->break_opt != -1)
			diffcore_break(options->repo,
				       options->break_opt);
		if (options->detect_rename)
			diffcore_rename(options);
		if (options->break_opt != -1)
			diffcore_merge_broken();
	}
	if (options->pickaxe_opts & DIFF_PICKAXE_KINDS_MASK)
		diffcore_pickaxe(options);
	if (options->orderfile)
		diffcore_order(options->orderfile);
	if (!options->found_follow)
		/* See try_to_follow_renames() in tree-diff.c */
		diff_resolve_rename_copy();
	diffcore_apply_filter(options);

	if (diff_queued_diff.nr && !options->flags.diff_from_contents)
		options->flags.has_changes = 1;
	else
		options->flags.has_changes = 0;

	options->found_follow = 0;
}