#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  resolved; } ;
typedef  TYPE_1__ git_merge_diff_list ;
struct TYPE_7__ {scalar_t__ type; scalar_t__ our_status; scalar_t__ their_status; int /*<<< orphan*/  their_entry; int /*<<< orphan*/  our_entry; } ;
typedef  TYPE_2__ git_merge_diff ;

/* Variables and functions */
 scalar_t__ GIT_DELTA_UNMODIFIED ; 
 scalar_t__ GIT_MERGE_DIFF_DIRECTORY_FILE ; 
 scalar_t__ GIT_MERGE_DIFF_RENAMED_ADDED ; 
 int /*<<< orphan*/  GIT_MERGE_INDEX_ENTRY_EXISTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_insert (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int merge_conflict_resolve_one_removed(
	int *resolved,
	git_merge_diff_list *diff_list,
	const git_merge_diff *conflict)
{
	int ours_empty, theirs_empty;
	int ours_changed, theirs_changed;
	int error = 0;

	assert(resolved && diff_list && conflict);

	*resolved = 0;

	if (conflict->type == GIT_MERGE_DIFF_DIRECTORY_FILE ||
		conflict->type == GIT_MERGE_DIFF_RENAMED_ADDED)
		return 0;

	ours_empty = !GIT_MERGE_INDEX_ENTRY_EXISTS(conflict->our_entry);
	theirs_empty = !GIT_MERGE_INDEX_ENTRY_EXISTS(conflict->their_entry);

	ours_changed = (conflict->our_status != GIT_DELTA_UNMODIFIED);
	theirs_changed = (conflict->their_status != GIT_DELTA_UNMODIFIED);

	/* Removed in both */
	if (ours_changed && ours_empty && theirs_empty)
		*resolved = 1;
	/* Removed in ours */
	else if (ours_empty && !theirs_changed)
		*resolved = 1;
	/* Removed in theirs */
	else if (!ours_changed && theirs_empty)
		*resolved = 1;

	if (*resolved)
		git_vector_insert(&diff_list->resolved, (git_merge_diff *)conflict);

	return error;
}