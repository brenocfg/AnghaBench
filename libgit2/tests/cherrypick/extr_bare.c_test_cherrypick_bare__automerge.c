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
struct merge_index_entry {int member_0; char* member_1; char* member_3; int /*<<< orphan*/  member_2; } ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_cherrypick_commit (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  merge_test_index (int /*<<< orphan*/ *,struct merge_index_entry*,int) ; 
 int /*<<< orphan*/  repo ; 

void test_cherrypick_bare__automerge(void)
{
	git_commit *head = NULL, *commit = NULL;
	git_index *index = NULL;
	git_oid head_oid, cherry_oid;

	struct merge_index_entry merge_index_entries[] = {
		{ 0100644, "38c05a857e831a7e759d83778bfc85d003e21c45", 0, "file1.txt" },
		{ 0100644, "a661b5dec1004e2c62654ded3762370c27cf266b", 0, "file2.txt" },
		{ 0100644, "df6b290e0bd6a89b01d69f66687e8abf385283ca", 0, "file3.txt" },
	};

	git_oid_fromstr(&head_oid, "d3d77487660ee3c0194ee01dc5eaf478782b1c7e");
	cl_git_pass(git_commit_lookup(&head, repo, &head_oid));

	git_oid_fromstr(&cherry_oid, "cfc4f0999a8367568e049af4f72e452d40828a15");
	cl_git_pass(git_commit_lookup(&commit, repo, &cherry_oid));

	cl_git_pass(git_cherrypick_commit(&index, repo, commit, head, 0, NULL));
	cl_assert(merge_test_index(index, merge_index_entries, 3));

	git_index_free(index);
	git_commit_free(head);
	git_commit_free(commit);
}