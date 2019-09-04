#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char** member_0; int member_1; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  git_fetch_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIRECTION_PUSH ; 
 int /*<<< orphan*/  GIT_EBAREREPO ; 
 int /*<<< orphan*/  GIT_FETCH_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connect_to_local_repository (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_create_anonymous (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_remote_fetch (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_upload (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_array ; 
 int /*<<< orphan*/  remote ; 
 int /*<<< orphan*/  repo ; 

void test_network_remote_local__push_to_non_bare_remote(void)
{
	char *refspec_strings[] = {
		"master:master",
	};
	git_strarray array = {
		refspec_strings,
		1,
	};
	/* Shouldn't be able to push to a non-bare remote */
	git_remote *localremote;
	git_fetch_options fetch_opts = GIT_FETCH_OPTIONS_INIT;

	/* Get some commits */
	connect_to_local_repository(cl_fixture("testrepo.git"));
	cl_git_pass(git_remote_fetch(remote, &array, &fetch_opts, NULL));

	/* Set up an empty non-bare repo to push into */
	{
		git_repository *remoterepo = NULL;
		cl_git_pass(git_repository_init(&remoterepo, "localnonbare", 0));
		git_repository_free(remoterepo);
	}

	/* Connect to the bare repo */
	cl_git_pass(git_remote_create_anonymous(&localremote, repo, "./localnonbare"));
	cl_git_pass(git_remote_connect(localremote, GIT_DIRECTION_PUSH, NULL, NULL, NULL));

	/* Try to push */
	cl_git_fail_with(GIT_EBAREREPO, git_remote_upload(localremote, &push_array, NULL));

	/* Clean up */
	git_remote_free(localremote);
	cl_fixture_cleanup("localbare.git");
}