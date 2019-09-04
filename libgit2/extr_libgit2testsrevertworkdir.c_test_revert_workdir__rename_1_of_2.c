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
struct merge_index_entry {int member_0; char* member_1; int member_2; char* member_3; } ;
struct TYPE_5__ {int rename_threshold; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {TYPE_1__ merge_opts; } ;
typedef  TYPE_2__ git_revert_options ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_MERGE_FIND_RENAMES ; 
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 TYPE_2__ GIT_REVERT_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  merge_test_index (int /*<<< orphan*/ ,struct merge_index_entry*,int) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  repo_index ; 

void test_revert_workdir__rename_1_of_2(void)
{
	git_commit *head, *commit;
	git_oid head_oid, revert_oid;
	git_revert_options opts = GIT_REVERT_OPTIONS_INIT;

	struct merge_index_entry merge_index_entries[] = {
		{ 0100644, "747726e021bc5f44b86de60e3032fd6f9f1b8383", 0, "file1.txt" },
		{ 0100644, "0ab09ea6d4c3634bdf6c221626d8b6f7dd890767", 0, "file2.txt" },
		{ 0100644, "f4e107c230d08a60fb419d19869f1f282b272d9c", 0, "file3.txt" },
		{ 0100644, "55acf326a69f0aab7a974ec53ffa55a50bcac14e", 3, "file4.txt" },
		{ 0100644, "55acf326a69f0aab7a974ec53ffa55a50bcac14e", 1, "file5.txt" },
		{ 0100644, "0f5bfcf58c558d865da6be0281d7795993646cee", 2, "file6.txt" },
	};

	opts.merge_opts.flags |= GIT_MERGE_FIND_RENAMES;
	opts.merge_opts.rename_threshold = 50;

	git_oid_fromstr(&head_oid, "cef56612d71a6af8d8015691e4865f7fece905b5");
	cl_git_pass(git_commit_lookup(&head, repo, &head_oid));
	cl_git_pass(git_reset(repo, (git_object *)head, GIT_RESET_HARD, NULL));

	git_oid_fromstr(&revert_oid, "55568c8de5322ff9a95d72747a239cdb64a19965");
	cl_git_pass(git_commit_lookup(&commit, repo, &revert_oid));
	cl_git_pass(git_revert(repo, commit, &opts));

	cl_assert(merge_test_index(repo_index, merge_index_entries, 6));

	git_commit_free(commit);
	git_commit_free(head);
}