#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_11__ {char* path; int mode; int /*<<< orphan*/  id; TYPE_1__ member_0; } ;
typedef  TYPE_3__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_10__ {int /*<<< orphan*/  path; } ;
struct TYPE_12__ {int /*<<< orphan*/  status; int /*<<< orphan*/  nfiles; TYPE_2__ old_file; } ;
typedef  TYPE_4__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int GIT_DELTA_CONFLICTED ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 TYPE_4__* git_diff_get_delta (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_conflict_add (int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * resolve_commit_oid_to_tree (int /*<<< orphan*/ ,char const*) ; 

void test_diff_workdir__to_index_conflicted(void) {
	const char *a_commit = "26a125ee1bf"; /* the current HEAD */
	git_index_entry ancestor = {{0}}, ours = {{0}}, theirs = {{0}};
	git_tree *a;
	git_index *index;
	git_diff *diff1, *diff2;
	const git_diff_delta *delta;

	g_repo = cl_git_sandbox_init("status");
	a = resolve_commit_oid_to_tree(g_repo, a_commit);

	cl_git_pass(git_repository_index(&index, g_repo));

	ancestor.path = ours.path = theirs.path = "_file";
	ancestor.mode = ours.mode = theirs.mode = 0100644;
	git_oid_fromstr(&ancestor.id, "d427e0b2e138501a3d15cc376077a3631e15bd46");
	git_oid_fromstr(&ours.id, "ee3fa1b8c00aff7fe02065fdb50864bb0d932ccf");
	git_oid_fromstr(&theirs.id, "2bd0a343aeef7a2cf0d158478966a6e587ff3863");
	cl_git_pass(git_index_conflict_add(index, &ancestor, &ours, &theirs));

	cl_git_pass(git_diff_tree_to_index(&diff1, g_repo, a, index, NULL));
	cl_git_pass(git_diff_index_to_workdir(&diff2, g_repo, index, NULL));
	cl_git_pass(git_diff_merge(diff1, diff2));

	cl_assert_equal_i(git_diff_num_deltas(diff1), 12);
	delta = git_diff_get_delta(diff1, 0);
	cl_assert_equal_s(delta->old_file.path, "_file");
	cl_assert_equal_i(delta->nfiles, 1);
	cl_assert_equal_i(delta->status, GIT_DELTA_CONFLICTED);

	git_diff_free(diff2);
	git_diff_free(diff1);
	git_index_free(index);
	git_tree_free(a);
}