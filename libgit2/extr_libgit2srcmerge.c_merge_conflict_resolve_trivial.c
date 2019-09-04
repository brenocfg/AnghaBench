#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  staged; } ;
typedef  TYPE_1__ git_merge_diff_list ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ our_status; scalar_t__ their_status; int /*<<< orphan*/  const their_entry; int /*<<< orphan*/  const our_entry; } ;
typedef  TYPE_2__ git_merge_diff ;
typedef  int /*<<< orphan*/  const git_index_entry ;

/* Variables and functions */
 scalar_t__ GIT_DELTA_RENAMED ; 
 scalar_t__ GIT_DELTA_UNMODIFIED ; 
 scalar_t__ GIT_MERGE_DIFF_DIRECTORY_FILE ; 
 scalar_t__ GIT_MERGE_DIFF_RENAMED_ADDED ; 
 scalar_t__ GIT_MERGE_INDEX_ENTRY_EXISTS (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int git_vector_insert (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ index_entry_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int merge_conflict_resolve_trivial(
	int *resolved,
	git_merge_diff_list *diff_list,
	const git_merge_diff *conflict)
{
	int ours_empty, theirs_empty;
	int ours_changed, theirs_changed, ours_theirs_differ;
	git_index_entry const *result = NULL;
	int error = 0;

	assert(resolved && diff_list && conflict);

	*resolved = 0;

	if (conflict->type == GIT_MERGE_DIFF_DIRECTORY_FILE ||
		conflict->type == GIT_MERGE_DIFF_RENAMED_ADDED)
		return 0;

	if (conflict->our_status == GIT_DELTA_RENAMED ||
		conflict->their_status == GIT_DELTA_RENAMED)
		return 0;

	ours_empty = !GIT_MERGE_INDEX_ENTRY_EXISTS(conflict->our_entry);
	theirs_empty = !GIT_MERGE_INDEX_ENTRY_EXISTS(conflict->their_entry);

	ours_changed = (conflict->our_status != GIT_DELTA_UNMODIFIED);
	theirs_changed = (conflict->their_status != GIT_DELTA_UNMODIFIED);
	ours_theirs_differ = ours_changed && theirs_changed &&
		index_entry_cmp(&conflict->our_entry, &conflict->their_entry);

	/*
	 * Note: with only one ancestor, some cases are not distinct:
	 *
	 * 16: ancest:anc1/anc2, head:anc1, remote:anc2 = result:no merge
	 * 3: ancest:(empty)^, head:head, remote:(empty) = result:no merge
	 * 2: ancest:(empty)^, head:(empty), remote:remote = result:no merge
	 *
	 * Note that the two cases that take D/F conflicts into account
	 * specifically do not need to be explicitly tested, as D/F conflicts
	 * would fail the *empty* test:
	 *
	 * 3ALT: ancest:(empty)+, head:head, remote:*empty* = result:head
	 * 2ALT: ancest:(empty)+, head:*empty*, remote:remote = result:remote
	 *
	 * Note that many of these cases need not be explicitly tested, as
	 * they simply degrade to "all different" cases (eg, 11):
	 *
	 * 4: ancest:(empty)^, head:head, remote:remote = result:no merge
	 * 7: ancest:ancest+, head:(empty), remote:remote = result:no merge
	 * 9: ancest:ancest+, head:head, remote:(empty) = result:no merge
	 * 11: ancest:ancest+, head:head, remote:remote = result:no merge
	 */

	/* 5ALT: ancest:*, head:head, remote:head = result:head */
	if (ours_changed && !ours_empty && !ours_theirs_differ)
		result = &conflict->our_entry;
	/* 6: ancest:ancest+, head:(empty), remote:(empty) = result:no merge */
	else if (ours_changed && ours_empty && theirs_empty)
		*resolved = 0;
	/* 8: ancest:ancest^, head:(empty), remote:ancest = result:no merge */
	else if (ours_empty && !theirs_changed)
		*resolved = 0;
	/* 10: ancest:ancest^, head:ancest, remote:(empty) = result:no merge */
	else if (!ours_changed && theirs_empty)
		*resolved = 0;
	/* 13: ancest:ancest+, head:head, remote:ancest = result:head */
	else if (ours_changed && !theirs_changed)
		result = &conflict->our_entry;
	/* 14: ancest:ancest+, head:ancest, remote:remote = result:remote */
	else if (!ours_changed && theirs_changed)
		result = &conflict->their_entry;
	else
		*resolved = 0;

	if (result != NULL &&
		GIT_MERGE_INDEX_ENTRY_EXISTS(*result) &&
		(error = git_vector_insert(&diff_list->staged, (void *)result)) >= 0)
		*resolved = 1;

	/* Note: trivial resolution does not update the REUC. */

	return error;
}