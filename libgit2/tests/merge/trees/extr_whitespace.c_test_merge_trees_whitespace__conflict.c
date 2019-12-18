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
 int /*<<< orphan*/  BRANCH_A_EOL ; 
 int /*<<< orphan*/  BRANCH_B_EOL ; 
 int /*<<< orphan*/  GIT_MERGE_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  merge_test_index (int /*<<< orphan*/ *,struct merge_index_entry*,int) ; 
 int /*<<< orphan*/  merge_trees_from_branches (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo ; 

void test_merge_trees_whitespace__conflict(void)
{
	git_index *index;
	git_merge_options opts = GIT_MERGE_OPTIONS_INIT;

	struct merge_index_entry merge_index_entries[] = {
		{ 0100644, "4026a6c83f39c56881c9ac62e7582db9e3d33a4f", 1, "test.txt" },
		{ 0100644, "c3b1fb31424c98072542cc8e42b48c92e52f494a", 2, "test.txt" },
		{ 0100644, "262f67de0de2e535a59ae1bc3c739601e98c354d", 3, "test.txt" },
	};

	cl_git_pass(merge_trees_from_branches(&index, repo, BRANCH_A_EOL, BRANCH_B_EOL, &opts));

	cl_assert(merge_test_index(index, merge_index_entries, 3));

	git_index_free(index);
}