#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct merge_index_entry {int member_0; char* member_1; int member_2; char* member_3; } ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_7__ {int /*<<< orphan*/  file_favor; } ;
struct TYPE_6__ {int checkout_strategy; } ;
struct TYPE_8__ {TYPE_2__ merge_opts; TYPE_1__ checkout_opts; } ;
typedef  TYPE_3__ git_cherrypick_options ;

/* Variables and functions */
 int GIT_CHECKOUT_SAFE ; 
 int GIT_CHECKOUT_USE_OURS ; 
 TYPE_3__ GIT_CHERRYPICK_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_MERGE_FILE_FAVOR_OURS ; 
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_cherrypick (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  merge_test_index (int /*<<< orphan*/ ,struct merge_index_entry*,int) ; 
 int /*<<< orphan*/  merge_test_workdir (int /*<<< orphan*/ ,struct merge_index_entry*,int) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  repo_index ; 

void test_cherrypick_workdir__conflict_use_ours(void)
{
	git_commit *head = NULL, *commit = NULL;
	git_oid head_oid, cherry_oid;
	git_cherrypick_options opts = GIT_CHERRYPICK_OPTIONS_INIT;

	struct merge_index_entry merge_index_entries[] = {
		{ 0100644, "242e7977ba73637822ffb265b46004b9b0e5153b", 0, "file1.txt" },
		{ 0100644, "a58ca3fee5eb68b11adc2703e5843f968c9dad1e", 1, "file2.txt" },
		{ 0100644, "bd6ffc8c6c41f0f85ff9e3d61c9479516bac0024", 2, "file2.txt" },
		{ 0100644, "563f6473a3858f99b80e5f93c660512ed38e1e6f", 3, "file2.txt" },
		{ 0100644, "28d9eb4208074ad1cc84e71ccc908b34573f05d2", 1, "file3.txt" },
		{ 0100644, "1124c2c1ae07b26fded662d6c3f3631d9dc16f88", 2, "file3.txt" },
		{ 0100644, "e233b9ed408a95e9d4b65fec7fc34943a556deb2", 3, "file3.txt" },
	};

	struct merge_index_entry merge_filesystem_entries[] = {
		{ 0100644, "242e7977ba73637822ffb265b46004b9b0e5153b", 0, "file1.txt" },
		{ 0100644, "bd6ffc8c6c41f0f85ff9e3d61c9479516bac0024", 0, "file2.txt" },
		{ 0100644, "1124c2c1ae07b26fded662d6c3f3631d9dc16f88", 0, "file3.txt" },
	};

	/* leave the index in a conflicted state, but checkout "ours" to the workdir */
	opts.checkout_opts.checkout_strategy = GIT_CHECKOUT_SAFE | GIT_CHECKOUT_USE_OURS;

	git_oid_fromstr(&head_oid, "bafbf6912c09505ac60575cd43d3f2aba3bd84d8");

	cl_git_pass(git_commit_lookup(&head, repo, &head_oid));
	cl_git_pass(git_reset(repo, (git_object *)head, GIT_RESET_HARD, NULL));

	git_oid_fromstr(&cherry_oid, "e9b63f3655b2ad80c0ff587389b5a9589a3a7110");
	cl_git_pass(git_commit_lookup(&commit, repo, &cherry_oid));
	cl_git_pass(git_cherrypick(repo, commit, &opts));

	cl_assert(merge_test_index(repo_index, merge_index_entries, 7));
	cl_assert(merge_test_workdir(repo, merge_filesystem_entries, 3));

	/* resolve conflicts in the index by taking "ours" */
	opts.merge_opts.file_favor = GIT_MERGE_FILE_FAVOR_OURS;

	cl_git_pass(git_reset(repo, (git_object *)head, GIT_RESET_HARD, NULL));
	cl_git_pass(git_cherrypick(repo, commit, &opts));

	cl_assert(merge_test_index(repo_index, merge_filesystem_entries, 3));
	cl_assert(merge_test_workdir(repo, merge_filesystem_entries, 3));

	git_commit_free(commit);
	git_commit_free(head);
}