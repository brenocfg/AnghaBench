#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ count; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_10__ {int* payload; int /*<<< orphan*/  transfer_progress; } ;
struct TYPE_9__ {TYPE_4__ callbacks; } ;
typedef  TYPE_2__ git_fetch_options ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 TYPE_2__ GIT_FETCH_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_REMOTE_ORIGIN ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 char* cl_git_path_url (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cleanup_local_repo ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_reference_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_list (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_remote_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_remote_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_prune (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int git_remote_prune_refs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_1__*) ; 
 int /*<<< orphan*/  transfer_cb ; 

void test_network_fetchlocal__fetchprune(void)
{
	git_repository *repo;
	git_remote *origin;
	int callcount = 0;
	git_strarray refnames = {0};
	git_reference *ref;
	git_config *config;
	git_repository *remote_repo = cl_git_sandbox_init("testrepo.git");
	const char *url = cl_git_path_url(git_repository_path(remote_repo));
	git_fetch_options options = GIT_FETCH_OPTIONS_INIT;

	options.callbacks.transfer_progress = transfer_cb;
	options.callbacks.payload = &callcount;

	cl_set_cleanup(&cleanup_local_repo, "foo");
	cl_git_pass(git_repository_init(&repo, "foo", true));

	cl_git_pass(git_remote_create(&origin, repo, GIT_REMOTE_ORIGIN, url));
	cl_git_pass(git_remote_fetch(origin, NULL, &options, NULL));

	cl_git_pass(git_reference_list(&refnames, repo));
	cl_assert_equal_i(19, (int)refnames.count);
	cl_assert(callcount > 0);
	git_strarray_free(&refnames);
	git_remote_free(origin);

	cl_git_pass(git_reference_lookup(&ref, remote_repo, "refs/heads/br2"));
	cl_git_pass(git_reference_delete(ref));
	git_reference_free(ref);

	cl_git_pass(git_remote_lookup(&origin, repo, GIT_REMOTE_ORIGIN));
	cl_git_pass(git_remote_fetch(origin, NULL, &options, NULL));
	cl_git_pass(git_remote_prune(origin, &options.callbacks));

	cl_git_pass(git_reference_list(&refnames, repo));
	cl_assert_equal_i(18, (int)refnames.count);
	git_strarray_free(&refnames);
	git_remote_free(origin);

	cl_git_pass(git_reference_lookup(&ref, remote_repo, "refs/heads/packed"));
	cl_git_pass(git_reference_delete(ref));
	git_reference_free(ref);

	cl_git_pass(git_repository_config(&config, repo));
	cl_git_pass(git_config_set_bool(config, "remote.origin.prune", 1));
	git_config_free(config);
	cl_git_pass(git_remote_lookup(&origin, repo, GIT_REMOTE_ORIGIN));
	cl_assert_equal_i(1, git_remote_prune_refs(origin));
	cl_git_pass(git_remote_fetch(origin, NULL, &options, NULL));

	cl_git_pass(git_reference_list(&refnames, repo));
	cl_assert_equal_i(17, (int)refnames.count);
	git_strarray_free(&refnames);
	git_remote_free(origin);

	git_repository_free(repo);
}