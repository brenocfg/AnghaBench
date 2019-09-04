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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_4__ {int mainline; } ;
typedef  TYPE_1__ git_cherrypick_options ;

/* Variables and functions */
 TYPE_1__ GIT_CHERRYPICK_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_cherrypick (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  merge_test_index (int /*<<< orphan*/ ,struct merge_index_entry*,int) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  repo_index ; 

void test_cherrypick_workdir__merge_second_parent(void)
{
	git_commit *head, *commit;
	git_oid head_oid, cherry_oid;
	git_cherrypick_options opts = GIT_CHERRYPICK_OPTIONS_INIT;

	struct merge_index_entry merge_index_entries[] = {
		{ 0100644, "487434cace79238a7091e2220611d4f20a765690", 0, "file1.txt" },
		{ 0100644, "e5183bfd18e3a0a691fadde2f0d5610b73282d31", 0, "file2.txt" },
		{ 0100644, "409a1bec58bf35348e8b62b72bb9c1f45cf5a587", 0, "file3.txt" },
	};

	opts.mainline = 2;

	git_oid_fromstr(&head_oid, "cfc4f0999a8367568e049af4f72e452d40828a15");
	cl_git_pass(git_commit_lookup(&head, repo, &head_oid));
	cl_git_pass(git_reset(repo, (git_object *)head, GIT_RESET_HARD, NULL));

	git_oid_fromstr(&cherry_oid, "abe4603bc7cd5b8167a267e0e2418fd2348f8cff");
	cl_git_pass(git_commit_lookup(&commit, repo, &cherry_oid));

	cl_git_pass(git_cherrypick(repo, commit, &opts));

	cl_assert(merge_test_index(repo_index, merge_index_entries, 3));

	git_commit_free(commit);
	git_commit_free(head);
}