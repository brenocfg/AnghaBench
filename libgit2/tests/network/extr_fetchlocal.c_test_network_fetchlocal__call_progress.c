#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_remote ;
struct TYPE_5__ {int* payload; int /*<<< orphan*/  sideband_progress; } ;
struct TYPE_6__ {TYPE_1__ callbacks; } ;
typedef  TYPE_2__ git_fetch_options ;

/* Variables and functions */
 TYPE_2__ GIT_FETCH_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fixture_url (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cleanup_local_repo ; 
 int /*<<< orphan*/  git_remote_create_with_fetchspec (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_remote_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int) ; 
 int /*<<< orphan*/  sideband_cb ; 

void test_network_fetchlocal__call_progress(void)
{
	git_repository *repo;
	git_remote *remote;
	git_fetch_options options = GIT_FETCH_OPTIONS_INIT;
	int callcount = 0;

	cl_git_pass(git_repository_init(&repo, "foo.git", true));
	cl_set_cleanup(cleanup_local_repo, "foo.git");

	cl_git_pass(git_remote_create_with_fetchspec(&remote, repo, "origin", cl_git_fixture_url("testrepo.git"), "+refs/heads/*:refs/heads/*"));

	options.callbacks.sideband_progress = sideband_cb;
	options.callbacks.payload = &callcount;

	cl_git_pass(git_remote_fetch(remote, NULL, &options, NULL));
	cl_assert(callcount != 0);

	git_remote_free(remote);
	git_repository_free(repo);
}