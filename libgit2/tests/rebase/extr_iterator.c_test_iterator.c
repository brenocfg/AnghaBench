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
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_4__ {int inmemory; } ;
typedef  TYPE_1__ git_rebase_options ;
typedef  int /*<<< orphan*/  git_rebase_operation ;
typedef  int /*<<< orphan*/  git_rebase ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITEROVER ; 
 int GIT_REBASE_NO_OPERATION ; 
 TYPE_1__ GIT_REBASE_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_fail (int) ; 
 int /*<<< orphan*/  cl_git_pass (int) ; 
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 int git_annotated_commit_from_ref (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int git_rebase_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_rebase_free (int /*<<< orphan*/ *) ; 
 int git_rebase_init (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int git_rebase_next (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_rebase_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  signature ; 
 int /*<<< orphan*/  test_operations (int /*<<< orphan*/ *,int) ; 

void test_iterator(bool inmemory)
{
	git_rebase *rebase;
	git_rebase_options opts = GIT_REBASE_OPTIONS_INIT;
	git_reference *branch_ref, *upstream_ref;
	git_annotated_commit *branch_head, *upstream_head;
	git_rebase_operation *rebase_operation;
	git_oid commit_id, expected_id;
	int error;

	opts.inmemory = inmemory;

	cl_git_pass(git_reference_lookup(&branch_ref, repo, "refs/heads/beef"));
	cl_git_pass(git_reference_lookup(&upstream_ref, repo, "refs/heads/master"));

	cl_git_pass(git_annotated_commit_from_ref(&branch_head, repo, branch_ref));
	cl_git_pass(git_annotated_commit_from_ref(&upstream_head, repo, upstream_ref));

	cl_git_pass(git_rebase_init(&rebase, repo, branch_head, upstream_head, NULL, &opts));
	test_operations(rebase, GIT_REBASE_NO_OPERATION);

	if (!inmemory) {
		git_rebase_free(rebase);
		cl_git_pass(git_rebase_open(&rebase, repo, NULL));
	}

	cl_git_pass(git_rebase_next(&rebase_operation, rebase));
	cl_git_pass(git_rebase_commit(&commit_id, rebase, NULL, signature,
		NULL, NULL));
	test_operations(rebase, 0);

	git_oid_fromstr(&expected_id, "776e4c48922799f903f03f5f6e51da8b01e4cce0");
	cl_assert_equal_oid(&expected_id, &commit_id);

	cl_git_pass(git_rebase_next(&rebase_operation, rebase));
	cl_git_pass(git_rebase_commit(&commit_id, rebase, NULL, signature,
		NULL, NULL));
	test_operations(rebase, 1);

	git_oid_fromstr(&expected_id, "ba1f9b4fd5cf8151f7818be2111cc0869f1eb95a");
	cl_assert_equal_oid(&expected_id, &commit_id);

	cl_git_pass(git_rebase_next(&rebase_operation, rebase));
	cl_git_pass(git_rebase_commit(&commit_id, rebase, NULL, signature,
		NULL, NULL));
	test_operations(rebase, 2);

	git_oid_fromstr(&expected_id, "948b12fe18b84f756223a61bece4c307787cd5d4");
	cl_assert_equal_oid(&expected_id, &commit_id);

	if (!inmemory) {
		git_rebase_free(rebase);
		cl_git_pass(git_rebase_open(&rebase, repo, NULL));
	}

	cl_git_pass(git_rebase_next(&rebase_operation, rebase));
	cl_git_pass(git_rebase_commit(&commit_id, rebase, NULL, signature,
		NULL, NULL));
	test_operations(rebase, 3);

	git_oid_fromstr(&expected_id, "d9d5d59d72c9968687f9462578d79878cd80e781");
	cl_assert_equal_oid(&expected_id, &commit_id);

	cl_git_pass(git_rebase_next(&rebase_operation, rebase));
	cl_git_pass(git_rebase_commit(&commit_id, rebase, NULL, signature,
		NULL, NULL));
	test_operations(rebase, 4);

	git_oid_fromstr(&expected_id, "9cf383c0a125d89e742c5dec58ed277dd07588b3");
	cl_assert_equal_oid(&expected_id, &commit_id);

	cl_git_fail(error = git_rebase_next(&rebase_operation, rebase));
	cl_assert_equal_i(GIT_ITEROVER, error);
	test_operations(rebase, 4);

	git_annotated_commit_free(branch_head);
	git_annotated_commit_free(upstream_head);
	git_reference_free(branch_ref);
	git_reference_free(upstream_ref);
	git_rebase_free(rebase);
}