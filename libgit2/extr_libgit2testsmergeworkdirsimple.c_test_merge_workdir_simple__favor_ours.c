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
struct merge_reuc_entry {int dummy; } ;
struct merge_index_entry {int member_0; char* member_1; char* member_3; int /*<<< orphan*/  member_2; } ;

/* Variables and functions */
 struct merge_index_entry ADDED_IN_MASTER_INDEX_ENTRY ; 
 struct merge_index_entry AUTOMERGEABLE_INDEX_ENTRY ; 
 struct merge_reuc_entry AUTOMERGEABLE_REUC_ENTRY ; 
 struct merge_index_entry CHANGED_IN_BRANCH_INDEX_ENTRY ; 
 struct merge_index_entry CHANGED_IN_MASTER_INDEX_ENTRY ; 
 struct merge_reuc_entry CONFLICTING_REUC_ENTRY ; 
 int /*<<< orphan*/  GIT_MERGE_FILE_FAVOR_OURS ; 
 struct merge_reuc_entry REMOVED_IN_BRANCH_REUC_ENTRY ; 
 struct merge_reuc_entry REMOVED_IN_MASTER_REUC_ENTRY ; 
 struct merge_index_entry UNCHANGED_INDEX_ENTRY ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  merge_simple_branch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  merge_test_index (int /*<<< orphan*/ ,struct merge_index_entry*,int) ; 
 int /*<<< orphan*/  merge_test_reuc (int /*<<< orphan*/ ,struct merge_reuc_entry*,int) ; 
 int /*<<< orphan*/  repo_index ; 

void test_merge_workdir_simple__favor_ours(void)
{
	struct merge_index_entry merge_index_entries[] = {
		ADDED_IN_MASTER_INDEX_ENTRY,
		AUTOMERGEABLE_INDEX_ENTRY,
		CHANGED_IN_BRANCH_INDEX_ENTRY,
		CHANGED_IN_MASTER_INDEX_ENTRY,
		{ 0100644, "4e886e602529caa9ab11d71f86634bd1b6e0de10", 0, "conflicting.txt" },
		UNCHANGED_INDEX_ENTRY,
	};

	struct merge_reuc_entry merge_reuc_entries[] = {
		AUTOMERGEABLE_REUC_ENTRY,
		CONFLICTING_REUC_ENTRY,
		REMOVED_IN_BRANCH_REUC_ENTRY,
		REMOVED_IN_MASTER_REUC_ENTRY,
	};

	merge_simple_branch(GIT_MERGE_FILE_FAVOR_OURS, 0);

	cl_assert(merge_test_index(repo_index, merge_index_entries, 6));
	cl_assert(merge_test_reuc(repo_index, merge_reuc_entries, 4));
}