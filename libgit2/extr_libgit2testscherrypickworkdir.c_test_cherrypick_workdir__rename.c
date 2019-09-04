#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct merge_index_entry {int member_0; char* member_1; char* member_3; int /*<<< orphan*/  member_2; } ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_5__ {int rename_threshold; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {TYPE_1__ merge_opts; } ;
typedef  TYPE_2__ git_cherrypick_options ;

/* Variables and functions */
 TYPE_2__ GIT_CHERRYPICK_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_MERGE_FIND_RENAMES ; 
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_cherrypick (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  merge_test_index (int /*<<< orphan*/ ,struct merge_index_entry*,int) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  repo_index ; 

void test_cherrypick_workdir__rename(void)
{
	git_commit *head, *commit;
	git_oid head_oid, cherry_oid;
	git_cherrypick_options opts = GIT_CHERRYPICK_OPTIONS_INIT;

	struct merge_index_entry merge_index_entries[] = {
		{ 0100644, "19c5c7207054604b69c84d08a7571ef9672bb5c2", 0, "file1.txt" },
		{ 0100644, "a58ca3fee5eb68b11adc2703e5843f968c9dad1e", 0, "file2.txt" },
		{ 0100644, "28d9eb4208074ad1cc84e71ccc908b34573f05d2", 0, "file3.txt.renamed" },
	};

	opts.merge_opts.flags |= GIT_MERGE_FIND_RENAMES;
	opts.merge_opts.rename_threshold = 50;

	git_oid_fromstr(&head_oid, "cfc4f0999a8367568e049af4f72e452d40828a15");
	cl_git_pass(git_commit_lookup(&head, repo, &head_oid));
	cl_git_pass(git_reset(repo, (git_object *)head, GIT_RESET_HARD, NULL));

	git_oid_fromstr(&cherry_oid, "2a26c7e88b285613b302ba76712bc998863f3cbc");
	cl_git_pass(git_commit_lookup(&commit, repo, &cherry_oid));
	cl_git_pass(git_cherrypick(repo, commit, &opts));

	cl_assert(merge_test_index(repo_index, merge_index_entries, 3));

	git_commit_free(commit);
	git_commit_free(head);
}