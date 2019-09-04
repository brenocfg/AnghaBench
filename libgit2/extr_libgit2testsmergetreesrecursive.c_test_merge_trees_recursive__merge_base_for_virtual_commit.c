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

void test_merge_trees_recursive__merge_base_for_virtual_commit(void)
{
	git_index *index;
	git_merge_options opts = GIT_MERGE_OPTIONS_INIT;

	struct merge_index_entry merge_index_entries[] = {
		{ 0100644, "1bde1883de4977ea3e664b315da951d1f614c3b1", 0, "targetfile.txt" },
		{ 0100644, "b7de2b52ba055688061355fad1599a5d214ce8f8", 1, "version.txt" },
		{ 0100644, "358efd6f589384fa8baf92234db9c7899a53916e", 2, "version.txt" },
		{ 0100644, "a664873b1c0b9a1ed300f8644dde536fdaa3a34f", 3, "version.txt" },
	};

	cl_git_pass(merge_commits_from_branches(&index, repo, "branchJ-1", "branchJ-2", &opts));

	cl_assert(merge_test_index(index, merge_index_entries, 4));

	git_index_free(index);
}