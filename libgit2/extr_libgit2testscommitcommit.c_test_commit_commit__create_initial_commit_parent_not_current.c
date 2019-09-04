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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_now (int /*<<< orphan*/ **,char*,char*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_commit_commit__create_initial_commit_parent_not_current(void)
{
	git_oid oid;
	git_oid original_oid;
	git_tree *tree;
	git_commit *commit;
	git_signature *s;

	git_oid_fromstr(&oid, "a65fedf39aefe402d3bb6e24df4d4f5fe4547750");
	cl_git_pass(git_commit_lookup(&commit, _repo, &oid));

	git_oid_fromstr(&oid, "944c0f6e4dfa41595e6eb3ceecdb14f50fe18162");
	cl_git_pass(git_tree_lookup(&tree, _repo, &oid));

	cl_git_pass(git_signature_now(&s, "alice", "alice@example.com"));

	cl_git_pass(git_reference_name_to_id(&original_oid, _repo, "HEAD"));

	cl_git_fail(git_commit_create(&oid, _repo, "HEAD", s, s,
				      NULL, "initial commit", tree, 0, NULL));

	cl_git_pass(git_reference_name_to_id(&oid, _repo, "HEAD"));

	cl_assert_equal_oid(&oid, &original_oid);

	git_tree_free(tree);
	git_commit_free(commit);
	git_signature_free(s);
}