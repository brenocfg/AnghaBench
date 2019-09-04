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
typedef  int /*<<< orphan*/  git_submodule ;
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_4__ {int /*<<< orphan*/ * remote_cb_payload; int /*<<< orphan*/  remote_cb; int /*<<< orphan*/ * repository_cb_payload; int /*<<< orphan*/  repository_cb; } ;
typedef  TYPE_1__ git_clone_options ;

/* Variables and functions */
 TYPE_1__ GIT_CLONE_OPTIONS_INIT ; 
 int /*<<< orphan*/  assert_submodule_exists (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_commit_create_from_ids (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_now (int /*<<< orphan*/ **,char*,char*) ; 
 int /*<<< orphan*/  git_submodule_add_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_add_setup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  just_return_origin ; 
 int /*<<< orphan*/  just_return_repo ; 

void test_clone_nonetwork__clone_submodule(void)
{
	git_clone_options clone_opts = GIT_CLONE_OPTIONS_INIT;
	git_index *index;
	git_oid tree_id, commit_id;
	git_submodule *sm;
	git_signature *sig;
	git_repository *sm_repo;

	cl_git_pass(git_repository_init(&g_repo, "willaddsubmodule", false));


	/* Create the submodule structure, clone into it and finalize */
	cl_git_pass(git_submodule_add_setup(&sm, g_repo, cl_fixture("testrepo.git"), "testrepo", true));

	clone_opts.repository_cb = just_return_repo;
	clone_opts.repository_cb_payload = sm;
	clone_opts.remote_cb = just_return_origin;
	clone_opts.remote_cb_payload = sm;
	cl_git_pass(git_clone(&sm_repo, cl_fixture("testrepo.git"), "testrepo", &clone_opts));
	cl_git_pass(git_submodule_add_finalize(sm));
	git_repository_free(sm_repo);
	git_submodule_free(sm);

	cl_git_pass(git_repository_index(&index, g_repo));
	cl_git_pass(git_index_write_tree(&tree_id, index));
	git_index_free(index);

	cl_git_pass(git_signature_now(&sig, "Submoduler", "submoduler@local"));
	cl_git_pass(git_commit_create_from_ids(&commit_id, g_repo, "HEAD", sig, sig, NULL, "A submodule\n",
					       &tree_id, 0, NULL));

	git_signature_free(sig);

	assert_submodule_exists(g_repo, "testrepo");
}