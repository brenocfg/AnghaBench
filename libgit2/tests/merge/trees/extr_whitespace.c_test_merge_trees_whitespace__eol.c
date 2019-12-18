#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct merge_index_entry {int member_0; char* member_1; char* member_3; int /*<<< orphan*/  member_2; } ;
struct TYPE_4__ {int /*<<< orphan*/  file_flags; } ;
typedef  TYPE_1__ git_merge_options ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  BRANCH_A_EOL ; 
 int /*<<< orphan*/  BRANCH_B_EOL ; 
 int /*<<< orphan*/  GIT_MERGE_FILE_IGNORE_WHITESPACE_EOL ; 
 TYPE_1__ GIT_MERGE_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  merge_test_index (int /*<<< orphan*/ *,struct merge_index_entry*,int) ; 
 int /*<<< orphan*/  merge_trees_from_branches (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  repo ; 

void test_merge_trees_whitespace__eol(void)
{
	git_index *index;
	git_merge_options opts = GIT_MERGE_OPTIONS_INIT;

	struct merge_index_entry merge_index_entries[] = {
		{ 0100644, "ee3c2aac8e03224c323b58ecb1f9eef616745467", 0, "test.txt" },
	};

	opts.file_flags |= GIT_MERGE_FILE_IGNORE_WHITESPACE_EOL;

	cl_git_pass(merge_trees_from_branches(&index, repo, BRANCH_A_EOL, BRANCH_B_EOL, &opts));

	cl_assert(merge_test_index(index, merge_index_entries, 1));

	git_index_free(index);
}