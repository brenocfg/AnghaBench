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
typedef  scalar_t__ timestamp_t ;
struct rev_info {int tag_objects; int blob_objects; int tree_objects; int ignore_missing_links; } ;
struct progress {int dummy; } ;
struct connectivity_progress {scalar_t__ count; struct progress* progress; } ;
struct bitmap_index {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_index_objects_to_pending (struct rev_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_one_ref ; 
 int /*<<< orphan*/  add_reflogs_to_pending (struct rev_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ add_unseen_recent_objects_to_traversal (struct rev_info*,scalar_t__) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  display_progress (struct progress*,scalar_t__) ; 
 int /*<<< orphan*/  for_each_ref (int /*<<< orphan*/ ,struct rev_info*) ; 
 int /*<<< orphan*/  free_bitmap_index (struct bitmap_index*) ; 
 int /*<<< orphan*/  head_ref (int /*<<< orphan*/ ,struct rev_info*) ; 
 int /*<<< orphan*/  mark_commit ; 
 int /*<<< orphan*/  mark_object ; 
 int /*<<< orphan*/  mark_object_seen ; 
 int /*<<< orphan*/  other_head_refs (int /*<<< orphan*/ ,struct rev_info*) ; 
 struct bitmap_index* prepare_bitmap_walk (struct rev_info*) ; 
 scalar_t__ prepare_revision_walk (struct rev_info*) ; 
 int /*<<< orphan*/  traverse_bitmap_commit_list (struct bitmap_index*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  traverse_commit_list (struct rev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct connectivity_progress*) ; 

void mark_reachable_objects(struct rev_info *revs, int mark_reflog,
			    timestamp_t mark_recent, struct progress *progress)
{
	struct connectivity_progress cp;
	struct bitmap_index *bitmap_git;

	/*
	 * Set up revision parsing, and mark us as being interested
	 * in all object types, not just commits.
	 */
	revs->tag_objects = 1;
	revs->blob_objects = 1;
	revs->tree_objects = 1;

	/* Add all refs from the index file */
	add_index_objects_to_pending(revs, 0);

	/* Add all external refs */
	for_each_ref(add_one_ref, revs);

	/* detached HEAD is not included in the list above */
	head_ref(add_one_ref, revs);
	other_head_refs(add_one_ref, revs);

	/* Add all reflog info */
	if (mark_reflog)
		add_reflogs_to_pending(revs, 0);

	cp.progress = progress;
	cp.count = 0;

	bitmap_git = prepare_bitmap_walk(revs);
	if (bitmap_git) {
		traverse_bitmap_commit_list(bitmap_git, mark_object_seen);
		free_bitmap_index(bitmap_git);
		return;
	}

	/*
	 * Set up the revision walk - this will move all commits
	 * from the pending list to the commit walking list.
	 */
	if (prepare_revision_walk(revs))
		die("revision walk setup failed");
	traverse_commit_list(revs, mark_commit, mark_object, &cp);

	if (mark_recent) {
		revs->ignore_missing_links = 1;
		if (add_unseen_recent_objects_to_traversal(revs, mark_recent))
			die("unable to mark recent objects");
		if (prepare_revision_walk(revs))
			die("revision walk setup failed");
		traverse_commit_list(revs, mark_commit, mark_object, &cp);
	}

	display_progress(cp.progress, cp.count);
}