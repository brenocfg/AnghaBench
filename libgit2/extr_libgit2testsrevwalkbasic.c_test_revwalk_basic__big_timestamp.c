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
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITEROVER ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  _walk ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int git_revwalk_next (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_push_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_new (int /*<<< orphan*/ **,char*,char*,long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  revwalk_basic_setup_walk (char*) ; 

void test_revwalk_basic__big_timestamp(void)
{
	git_reference *head;
	git_commit *tip;
	git_signature *sig;
	git_tree *tree;
	git_oid id;
	int error;

	revwalk_basic_setup_walk("testrepo.git");

	cl_git_pass(git_repository_head(&head, _repo));
	cl_git_pass(git_reference_peel((git_object **) &tip, head, GIT_OBJECT_COMMIT));

	/* Commit with a far-ahead timestamp, we should be able to parse it in the revwalk */
	cl_git_pass(git_signature_new(&sig, "Joe", "joe@example.com", 2399662595ll, 0));
	cl_git_pass(git_commit_tree(&tree, tip));

	cl_git_pass(git_commit_create(&id, _repo, "HEAD", sig, sig, NULL, "some message", tree, 1,
		(const git_commit **)&tip));

	cl_git_pass(git_revwalk_push_head(_walk));

	while ((error = git_revwalk_next(&id, _walk)) == 0) {
		/* nothing */
	}

	cl_assert_equal_i(GIT_ITEROVER, error);

	git_tree_free(tree);
	git_commit_free(tip);
	git_reference_free(head);
	git_signature_free(sig);

}