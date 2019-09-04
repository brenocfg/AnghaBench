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
struct TYPE_4__ {int mainline; } ;
typedef  TYPE_1__ git_revert_options ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 TYPE_1__ GIT_REVERT_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  merge_test_index (int /*<<< orphan*/ ,struct merge_index_entry*,int) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  repo_index ; 

void test_revert_workdir__merge_first_parent(void)
{
	git_commit *head;
	git_oid head_oid;
	git_revert_options opts = GIT_REVERT_OPTIONS_INIT;

	struct merge_index_entry merge_index_entries[] = {
		{ 0100644, "296a6d3be1dff05c5d1f631d2459389fa7b619eb", 0, "file-mainline.txt" },
		{ 0100644, "0cdb66192ee192f70f891f05a47636057420e871", 0, "file1.txt" },
		{ 0100644, "73ec36fa120f8066963a0bc9105bb273dbd903d7", 0, "file2.txt" },
	};

	opts.mainline = 1;

	git_oid_fromstr(&head_oid, "5acdc74af27172ec491d213ee36cea7eb9ef2579");
	cl_git_pass(git_commit_lookup(&head, repo, &head_oid));
	cl_git_pass(git_reset(repo, (git_object *)head, GIT_RESET_HARD, NULL));

	cl_git_pass(git_revert(repo, head, &opts));

	cl_assert(merge_test_index(repo_index, merge_index_entries, 3));

	git_commit_free(head);
}