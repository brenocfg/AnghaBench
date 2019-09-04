#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_13__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ git_diff_options ;
struct TYPE_14__ {int flags; } ;
typedef  TYPE_4__ git_diff_find_options ;
struct TYPE_12__ {int /*<<< orphan*/  path; } ;
struct TYPE_11__ {int /*<<< orphan*/  path; } ;
struct TYPE_15__ {TYPE_2__ new_file; TYPE_1__ old_file; int /*<<< orphan*/  status; } ;
typedef  TYPE_5__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int GIT_DELTA_RENAMED ; 
 int GIT_DIFF_FIND_FOR_UNTRACKED ; 
 TYPE_4__ GIT_DIFF_FIND_OPTIONS_INIT ; 
 int GIT_DIFF_FIND_RENAMES ; 
 int /*<<< orphan*/  GIT_DIFF_INCLUDE_UNTRACKED ; 
 TYPE_3__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rmfile (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_commit_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_find_similar (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 TYPE_5__* git_diff_get_delta (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_new (int /*<<< orphan*/ **,char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_diff_rename__test_small_files(void)
{
	git_index *index;
	git_reference *head_reference;
	git_commit *head_commit;
	git_tree *head_tree;
	git_tree *commit_tree;
	git_signature *signature;
	git_diff *diff;
	git_oid oid;
	const git_diff_delta *delta;
	git_diff_options diff_options = GIT_DIFF_OPTIONS_INIT;
	git_diff_find_options find_options = GIT_DIFF_FIND_OPTIONS_INIT;

	cl_git_pass(git_repository_index(&index, g_repo));

	cl_git_mkfile("renames/small.txt", "Hello World!\n");
	cl_git_pass(git_index_add_bypath(index, "small.txt"));

	cl_git_pass(git_repository_head(&head_reference, g_repo));
	cl_git_pass(git_reference_peel((git_object**)&head_commit, head_reference, GIT_OBJECT_COMMIT));
	cl_git_pass(git_commit_tree(&head_tree, head_commit));
	cl_git_pass(git_index_write_tree(&oid, index));
	cl_git_pass(git_tree_lookup(&commit_tree, g_repo, &oid));
	cl_git_pass(git_signature_new(&signature, "Rename", "rename@example.com", 1404157834, 0));
	cl_git_pass(git_commit_create(&oid, g_repo, "HEAD", signature, signature, NULL, "Test commit", commit_tree, 1, (const git_commit**)&head_commit));

	cl_git_mkfile("renames/copy.txt", "Hello World!\n");
	cl_git_rmfile("renames/small.txt");

	diff_options.flags = GIT_DIFF_INCLUDE_UNTRACKED;
	cl_git_pass(git_diff_tree_to_workdir(&diff, g_repo, commit_tree, &diff_options));
	find_options.flags = GIT_DIFF_FIND_RENAMES | GIT_DIFF_FIND_FOR_UNTRACKED;
	cl_git_pass(git_diff_find_similar(diff, &find_options));

	cl_assert_equal_i(git_diff_num_deltas(diff), 1);
	delta = git_diff_get_delta(diff, 0);
	cl_assert_equal_i(delta->status, GIT_DELTA_RENAMED);
	cl_assert_equal_s(delta->old_file.path, "small.txt");
	cl_assert_equal_s(delta->new_file.path, "copy.txt");

	git_diff_free(diff);
	git_signature_free(signature);
	git_tree_free(commit_tree);
	git_tree_free(head_tree);
	git_commit_free(head_commit);
	git_reference_free(head_reference);
	git_index_free(index);
}