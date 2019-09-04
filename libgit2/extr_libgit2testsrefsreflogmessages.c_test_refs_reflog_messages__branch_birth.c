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

/* Variables and functions */
 char* GIT_HEAD_FILE ; 
 int /*<<< orphan*/  GIT_OBJECT_TREE ; 
 int /*<<< orphan*/  cl_assert_equal_i (size_t,size_t) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_commit_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_set_head (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_now (int /*<<< orphan*/ **,char*,char*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 size_t reflog_entrycount (int /*<<< orphan*/ ,char*) ; 

void test_refs_reflog_messages__branch_birth(void)
{
	git_signature *sig;
	git_oid id;
	git_tree *tree;
	git_reference *ref;
	const char *msg;
	size_t nentries, nentries_after;

	nentries = reflog_entrycount(g_repo, GIT_HEAD_FILE);

	cl_git_pass(git_signature_now(&sig, "me", "foo@example.com"));

	cl_git_pass(git_repository_head(&ref, g_repo));
	cl_git_pass(git_reference_peel((git_object **) &tree, ref, GIT_OBJECT_TREE));

	cl_git_pass(git_repository_set_head(g_repo, "refs/heads/orphan"));

	nentries_after = reflog_entrycount(g_repo, GIT_HEAD_FILE);

	cl_assert_equal_i(nentries, nentries_after);

	msg = "message 2";
	cl_git_pass(git_commit_create(&id, g_repo, "HEAD", sig, sig, NULL, msg, tree, 0, NULL));

	cl_assert_equal_i(1, reflog_entrycount(g_repo, "refs/heads/orphan"));

	nentries_after = reflog_entrycount(g_repo, GIT_HEAD_FILE);

	cl_assert_equal_i(nentries + 1, nentries_after);

	git_signature_free(sig);
	git_tree_free(tree);
	git_reference_free(ref);
}