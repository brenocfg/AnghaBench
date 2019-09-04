#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct merge_index_entry {int member_0; char* member_1; int member_2; char* member_3; } ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_annotated_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* git_index_get_bypath (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_merge (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int merge_test_index (int /*<<< orphan*/ ,struct merge_index_entry*,int) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  repo_index ; 

void test_merge_workdir_simple__binary(void)
{
	git_oid our_oid, their_oid, our_file_oid;
	git_commit *our_commit;
	git_annotated_commit *their_head;
	const git_index_entry *binary_entry;

	struct merge_index_entry merge_index_entries[] = {
		{ 0100644, "1c51d885170f57a0c4e8c69ff6363d91a5b51f85", 1, "binary" },
		{ 0100644, "23ed141a6ae1e798b2f721afedbe947c119111ba", 2, "binary" },
		{ 0100644, "836b8b82b26cab22eaaed8820877c76d6c8bca19", 3, "binary" },
	};

	cl_git_pass(git_oid_fromstr(&our_oid, "cc338e4710c9b257106b8d16d82f86458d5beaf1"));
	cl_git_pass(git_oid_fromstr(&their_oid, "ad01aebfdf2ac13145efafe3f9fcf798882f1730"));

	cl_git_pass(git_commit_lookup(&our_commit, repo, &our_oid));
	cl_git_pass(git_reset(repo, (git_object *)our_commit, GIT_RESET_HARD, NULL));

	cl_git_pass(git_annotated_commit_lookup(&their_head, repo, &their_oid));

	cl_git_pass(git_merge(repo, (const git_annotated_commit **)&their_head, 1, NULL, NULL));

	cl_assert(merge_test_index(repo_index, merge_index_entries, 3));

	cl_git_pass(git_index_add_bypath(repo_index, "binary"));
	cl_assert((binary_entry = git_index_get_bypath(repo_index, "binary", 0)) != NULL);

	cl_git_pass(git_oid_fromstr(&our_file_oid, "23ed141a6ae1e798b2f721afedbe947c119111ba"));
	cl_assert(git_oid_cmp(&binary_entry->id, &our_file_oid) == 0);

	git_annotated_commit_free(their_head);
	git_commit_free(our_commit);
}