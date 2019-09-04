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

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIRECTION_PUSH ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 char* cl_git_path_url (char*) ; 
 int /*<<< orphan*/  connect_to_local_repository (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_create_anonymous (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_remote_fetch (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_upload (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int) ; 
 int /*<<< orphan*/  push_array ; 
 int /*<<< orphan*/  remote ; 
 int /*<<< orphan*/  repo ; 

void test_network_remote_local__push_to_bare_remote_with_file_url(void)
{
	char *refspec_strings[] = {
		"master:master",
	};
	git_strarray array = {
		refspec_strings,
		1,
	};
	/* Should be able to push to a bare remote */
	git_remote *localremote;
	const char *url;

	/* Get some commits */
	connect_to_local_repository(cl_fixture("testrepo.git"));
	cl_git_pass(git_remote_fetch(remote, &array, NULL, NULL));

	/* Set up an empty bare repo to push into */
	{
		git_repository *localbarerepo;
		cl_git_pass(git_repository_init(&localbarerepo, "./localbare.git", 1));
		git_repository_free(localbarerepo);
	}

	/* Create a file URL */
	url = cl_git_path_url("./localbare.git");

	/* Connect to the bare repo */
	cl_git_pass(git_remote_create_anonymous(&localremote, repo, url));
	cl_git_pass(git_remote_connect(localremote, GIT_DIRECTION_PUSH, NULL, NULL, NULL));

	/* Try to push */
	cl_git_pass(git_remote_upload(localremote, &push_array, NULL));

	/* Clean up */
	git_remote_free(localremote);
	cl_fixture_cleanup("localbare.git");
}