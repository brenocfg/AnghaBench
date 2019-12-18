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
typedef  int /*<<< orphan*/  git_submodule ;
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  assert_submodule_exists (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_commit_create_from_ids (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_now (int /*<<< orphan*/ **,char*,char*) ; 
 int /*<<< orphan*/  git_submodule_add_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_add_setup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  git_submodule_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 

void test_submodule_add__submodule_clone(void)
{
	git_oid tree_id, commit_id;
	git_signature *sig;
	git_submodule *sm;
	git_index *index;

	g_repo = cl_git_sandbox_init("empty_standard_repo");

	/* Create the submodule structure, clone into it and finalize */
	cl_git_pass(git_submodule_add_setup(&sm, g_repo, cl_fixture("testrepo.git"), "testrepo-add", true));
	cl_git_pass(git_submodule_clone(NULL, sm, NULL));
	cl_git_pass(git_submodule_add_finalize(sm));

	/* Create the submodule commit */
	cl_git_pass(git_repository_index(&index, g_repo));
	cl_git_pass(git_index_write_tree(&tree_id, index));
	cl_git_pass(git_signature_now(&sig, "Submoduler", "submoduler@local"));
	cl_git_pass(git_commit_create_from_ids(&commit_id, g_repo, "HEAD", sig, sig, NULL, "A submodule\n",
					       &tree_id, 0, NULL));

	assert_submodule_exists(g_repo, "testrepo-add");

	git_signature_free(sig);
	git_submodule_free(sm);
	git_index_free(index);
}