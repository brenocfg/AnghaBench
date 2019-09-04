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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REMOTE_ORIGIN ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 char* cl_git_path_url (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cleanup_local_repo ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_remote_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_prune_refs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ *) ; 

void test_network_fetchlocal__prune_load_remote_prune_config(void)
{
	git_repository *repo;
	git_remote *origin;
	git_config *config;
	git_repository *remote_repo = cl_git_sandbox_init("testrepo.git");
	const char *url = cl_git_path_url(git_repository_path(remote_repo));

	cl_set_cleanup(&cleanup_local_repo, "foo");
	cl_git_pass(git_repository_init(&repo, "foo", true));

	cl_git_pass(git_repository_config(&config, repo));
	cl_git_pass(git_config_set_bool(config, "remote.origin.prune", 1));

	cl_git_pass(git_remote_create(&origin, repo, GIT_REMOTE_ORIGIN, url));
	cl_assert_equal_i(1, git_remote_prune_refs(origin));

	git_config_free(config);
	git_remote_free(origin);
	git_repository_free(repo);
}