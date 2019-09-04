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
struct merge_index_entry {int member_0; char* member_1; int member_2; char* member_3; } ;
typedef  int /*<<< orphan*/  git_merge_options ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_MERGE_OPTIONS_INIT ; 
 int /*<<< orphan*/  THEIRS_UNRELATED_BRANCH ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  merge_test_index (int /*<<< orphan*/ *,struct merge_index_entry*,int) ; 
 int /*<<< orphan*/  merge_trees_from_branches (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo ; 

void test_merge_trees_automerge__unrelated(void)
{
	git_index *index;
	git_merge_options opts = GIT_MERGE_OPTIONS_INIT;

	struct merge_index_entry merge_index_entries[] = {
		{ 0100644, "233c0919c998ed110a4b6ff36f353aec8b713487", 0, "added-in-master.txt" },
		{ 0100644, "ee3fa1b8c00aff7fe02065fdb50864bb0d932ccf", 2, "automergeable.txt" },
		{ 0100644, "d07ec190c306ec690bac349e87d01c4358e49bb2", 3, "automergeable.txt" },
		{ 0100644, "ab6c44a2e84492ad4b41bb6bac87353e9d02ac8b", 0, "changed-in-branch.txt" },
		{ 0100644, "11deab00b2d3a6f5a3073988ac050c2d7b6655e2", 0, "changed-in-master.txt" },
		{ 0100644, "4e886e602529caa9ab11d71f86634bd1b6e0de10", 2, "conflicting.txt" },
		{ 0100644, "4b253da36a0ae8bfce63aeabd8c5b58429925594", 3, "conflicting.txt" },
		{ 0100644, "ef58fdd8086c243bdc81f99e379acacfd21d32d6", 0, "new-in-unrelated1.txt" },
		{ 0100644, "948ba6e701c1edab0c2d394fb7c5538334129793", 0, "new-in-unrelated2.txt" },
		{ 0100644, "dfe3f22baa1f6fce5447901c3086bae368de6bdd", 0, "removed-in-branch.txt" },
		{ 0100644, "c8f06f2e3bb2964174677e91f0abead0e43c9e5d", 0, "unchanged.txt" },
	};

	cl_git_pass(merge_trees_from_branches(&index, repo, "master", THEIRS_UNRELATED_BRANCH, &opts));

	cl_assert(merge_test_index(index, merge_index_entries, 11));

	git_index_free(index);
}