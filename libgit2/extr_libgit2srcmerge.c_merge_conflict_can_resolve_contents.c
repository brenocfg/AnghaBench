#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  path; int /*<<< orphan*/  mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  path; int /*<<< orphan*/  mode; } ;
struct TYPE_6__ {scalar_t__ type; int our_status; int their_status; TYPE_4__ their_entry; TYPE_1__ ancestor_entry; TYPE_4__ our_entry; } ;
typedef  TYPE_2__ git_merge_diff ;

/* Variables and functions */
 int GIT_DELTA_RENAMED ; 
 scalar_t__ GIT_MERGE_DIFF_BOTH_RENAMED_2_TO_1 ; 
 scalar_t__ GIT_MERGE_DIFF_DIRECTORY_FILE ; 
 scalar_t__ GIT_MERGE_DIFF_RENAMED_ADDED ; 
 int /*<<< orphan*/  GIT_MERGE_INDEX_ENTRY_EXISTS (TYPE_4__) ; 
 scalar_t__ S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool merge_conflict_can_resolve_contents(
	const git_merge_diff *conflict)
{
	if (!GIT_MERGE_INDEX_ENTRY_EXISTS(conflict->our_entry) ||
		!GIT_MERGE_INDEX_ENTRY_EXISTS(conflict->their_entry))
		return false;

	/* Reject D/F conflicts */
	if (conflict->type == GIT_MERGE_DIFF_DIRECTORY_FILE)
		return false;

	/* Reject submodules. */
	if (S_ISGITLINK(conflict->ancestor_entry.mode) ||
		S_ISGITLINK(conflict->our_entry.mode) ||
		S_ISGITLINK(conflict->their_entry.mode))
		return false;

	/* Reject link/file conflicts. */
	if ((S_ISLNK(conflict->ancestor_entry.mode) ^
			S_ISLNK(conflict->our_entry.mode)) ||
		(S_ISLNK(conflict->ancestor_entry.mode) ^
			S_ISLNK(conflict->their_entry.mode)))
		return false;

	/* Reject name conflicts */
	if (conflict->type == GIT_MERGE_DIFF_BOTH_RENAMED_2_TO_1 ||
		conflict->type == GIT_MERGE_DIFF_RENAMED_ADDED)
		return false;

	if ((conflict->our_status & GIT_DELTA_RENAMED) == GIT_DELTA_RENAMED &&
		(conflict->their_status & GIT_DELTA_RENAMED) == GIT_DELTA_RENAMED &&
		strcmp(conflict->ancestor_entry.path, conflict->their_entry.path) != 0)
		return false;

	return true;
}