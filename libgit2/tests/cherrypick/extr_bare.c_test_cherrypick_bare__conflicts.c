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

void test_cherrypick_bare__conflicts(void)
{
	git_commit *head = NULL, *commit = NULL;
	git_index *index = NULL;
	git_oid head_oid, cherry_oid;

	struct merge_index_entry merge_index_entries[] = {
		{ 0100644, "242e7977ba73637822ffb265b46004b9b0e5153b", 0, "file1.txt" },
		{ 0100644, "a58ca3fee5eb68b11adc2703e5843f968c9dad1e", 1, "file2.txt" },
		{ 0100644, "bd6ffc8c6c41f0f85ff9e3d61c9479516bac0024", 2, "file2.txt" },
		{ 0100644, "563f6473a3858f99b80e5f93c660512ed38e1e6f", 3, "file2.txt" },
		{ 0100644, "28d9eb4208074ad1cc84e71ccc908b34573f05d2", 1, "file3.txt" },
		{ 0100644, "1124c2c1ae07b26fded662d6c3f3631d9dc16f88", 2, "file3.txt" },
		{ 0100644, "e233b9ed408a95e9d4b65fec7fc34943a556deb2", 3, "file3.txt" },
	};

	git_oid_fromstr(&head_oid, "bafbf6912c09505ac60575cd43d3f2aba3bd84d8");
	cl_git_pass(git_commit_lookup(&head, repo, &head_oid));

	git_oid_fromstr(&cherry_oid, "e9b63f3655b2ad80c0ff587389b5a9589a3a7110");
	cl_git_pass(git_commit_lookup(&commit, repo, &cherry_oid));

	cl_git_pass(git_cherrypick_commit(&index, repo, commit, head, 0, NULL));
	cl_assert(merge_test_index(index, merge_index_entries, 7));

	git_index_free(index);
	git_commit_free(head);
	git_commit_free(commit);
}