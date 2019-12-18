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
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  merge_commits_from_branches (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  merge_test_index (int /*<<< orphan*/ *,struct merge_index_entry*,int) ; 
 int /*<<< orphan*/  repo ; 

void test_merge_trees_recursive__merge_base_for_virtual_commit_2(void)
{
	git_index *index;
	git_merge_options opts = GIT_MERGE_OPTIONS_INIT;

	struct merge_index_entry merge_index_entries[] = {
		{ 0100644, "4a06b258fed8a4d15967ec4253ae7366b70f727d", 0, "targetfile.txt" },
		{ 0100644, "b6bd0f9952f396e757d3f91e08c59a7e91707201", 1, "version.txt" },
		{ 0100644, "f0856993e005c0d8ed2dc7cdc222cc1d89fb3c77", 2, "version.txt" },
		{ 0100644, "2cba583804a4a6fad1baf97c959be447238d1489", 3, "version.txt" },
	};

	cl_git_pass(merge_commits_from_branches(&index, repo, "branchK-1", "branchK-2", &opts));

	cl_assert(merge_test_index(index, merge_index_entries, 4));

	git_index_free(index);
}