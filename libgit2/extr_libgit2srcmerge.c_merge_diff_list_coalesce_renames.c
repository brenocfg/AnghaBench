#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct merge_diff_similarity {scalar_t__ similarity; size_t other_idx; } ;
struct TYPE_11__ {scalar_t__ rename_threshold; } ;
typedef  TYPE_2__ git_merge_options ;
struct TYPE_10__ {size_t length; TYPE_4__** contents; } ;
struct TYPE_12__ {TYPE_1__ conflicts; } ;
typedef  TYPE_3__ git_merge_diff_list ;
struct TYPE_13__ {int /*<<< orphan*/  their_status; int /*<<< orphan*/  their_entry; int /*<<< orphan*/  our_status; int /*<<< orphan*/  our_entry; } ;
typedef  TYPE_4__ git_merge_diff ;

/* Variables and functions */
 scalar_t__ GIT_MERGE_INDEX_ENTRY_EXISTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  merge_diff_coalesce_rename (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  merge_diff_mark_rename_conflict (TYPE_3__*,struct merge_diff_similarity*,int,size_t,struct merge_diff_similarity*,int,size_t,TYPE_4__*,TYPE_2__ const*) ; 

__attribute__((used)) static void merge_diff_list_coalesce_renames(
	git_merge_diff_list *diff_list,
	struct merge_diff_similarity *similarity_ours,
	struct merge_diff_similarity *similarity_theirs,
	const git_merge_options *opts)
{
	size_t i;
	bool ours_renamed = 0, theirs_renamed = 0;
	size_t ours_source_idx = 0, theirs_source_idx = 0;
	git_merge_diff *ours_source, *theirs_source, *target;

	for (i = 0; i < diff_list->conflicts.length; i++) {
		target = diff_list->conflicts.contents[i];

		ours_renamed = 0;
		theirs_renamed = 0;

		if (GIT_MERGE_INDEX_ENTRY_EXISTS(target->our_entry) &&
			similarity_ours[i].similarity >= opts->rename_threshold) {
			ours_source_idx = similarity_ours[i].other_idx;

			ours_source = diff_list->conflicts.contents[ours_source_idx];

			merge_diff_coalesce_rename(
				&ours_source->our_entry,
				&ours_source->our_status,
				&target->our_entry,
				&target->our_status);

			similarity_ours[ours_source_idx].similarity = 0;
			similarity_ours[i].similarity = 0;

			ours_renamed = 1;
		}

		/* insufficient to determine direction */
		if (GIT_MERGE_INDEX_ENTRY_EXISTS(target->their_entry) &&
			similarity_theirs[i].similarity >= opts->rename_threshold) {
			theirs_source_idx = similarity_theirs[i].other_idx;

			theirs_source = diff_list->conflicts.contents[theirs_source_idx];

			merge_diff_coalesce_rename(
				&theirs_source->their_entry,
				&theirs_source->their_status,
				&target->their_entry,
				&target->their_status);

			similarity_theirs[theirs_source_idx].similarity = 0;
			similarity_theirs[i].similarity = 0;

			theirs_renamed = 1;
		}

		merge_diff_mark_rename_conflict(diff_list,
			similarity_ours, ours_renamed, ours_source_idx,
			similarity_theirs, theirs_renamed, theirs_source_idx,
			target, opts);
	}
}