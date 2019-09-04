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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_rebase ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  GIT_REPOSITORY_STATE_NONE ; 
 int /*<<< orphan*/  GIT_REPOSITORY_STATE_REBASE_MERGE ; 
 int /*<<< orphan*/  cl_assert_equal_file (char*,int,char*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_annotated_commit_from_ref (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_rebase_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_rebase_init (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 

void test_rebase_setup__merge_onto_and_upstream(void)
{
	git_rebase *rebase;
	git_reference *branch1_ref, *branch2_ref, *onto_ref;
	git_annotated_commit *branch1_head, *branch2_head, *onto_head;
	git_reference *head;
	git_commit *head_commit;
	git_oid head_id;

	cl_assert_equal_i(GIT_REPOSITORY_STATE_NONE, git_repository_state(repo));

	cl_git_pass(git_reference_lookup(&branch1_ref, repo, "refs/heads/gravy"));
	cl_git_pass(git_reference_lookup(&branch2_ref, repo, "refs/heads/veal"));
	cl_git_pass(git_reference_lookup(&onto_ref, repo, "refs/heads/master"));

	cl_git_pass(git_annotated_commit_from_ref(&branch1_head, repo, branch1_ref));
	cl_git_pass(git_annotated_commit_from_ref(&branch2_head, repo, branch2_ref));
	cl_git_pass(git_annotated_commit_from_ref(&onto_head, repo, onto_ref));

	cl_git_pass(git_rebase_init(&rebase, repo, branch1_head, branch2_head, onto_head, NULL));

	git_oid_fromstr(&head_id, "efad0b11c47cb2f0220cbd6f5b0f93bb99064b00");
	cl_git_pass(git_repository_head(&head, repo));
	cl_git_pass(git_reference_peel((git_object **)&head_commit, head, GIT_OBJECT_COMMIT));
	cl_assert_equal_oid(&head_id, git_commit_id(head_commit));

	cl_assert_equal_file("d616d97082eb7bb2dc6f180a7cca940993b7a56f\n", 41, "rebase/.git/ORIG_HEAD");

	cl_assert_equal_i(GIT_REPOSITORY_STATE_REBASE_MERGE, git_repository_state(repo));

	cl_assert_equal_file("d616d97082eb7bb2dc6f180a7cca940993b7a56f\n", 41, "rebase/.git/rebase-merge/cmt.1");
	cl_assert_equal_file("1\n", 2, "rebase/.git/rebase-merge/end");
	cl_assert_equal_file("efad0b11c47cb2f0220cbd6f5b0f93bb99064b00\n", 41, "rebase/.git/rebase-merge/onto");
	cl_assert_equal_file("master\n", 7, "rebase/.git/rebase-merge/onto_name");
	cl_assert_equal_file("d616d97082eb7bb2dc6f180a7cca940993b7a56f\n", 41, "rebase/.git/rebase-merge/orig-head");

	git_commit_free(head_commit);
	git_reference_free(head);
	git_annotated_commit_free(branch1_head);
	git_annotated_commit_free(branch2_head);
	git_annotated_commit_free(onto_head);
	git_reference_free(branch1_ref);
	git_reference_free(branch2_ref);
	git_reference_free(onto_ref);
	git_rebase_free(rebase);
}