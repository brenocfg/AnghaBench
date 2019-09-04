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

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIRECTION_FETCH ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_path_url (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_path_buf ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_connected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_create_anonymous (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_new (int /*<<< orphan*/ **) ; 

void test_network_remote_local__anonymous_remote_inmemory_repo(void)
{
	git_repository *inmemory;
	git_remote *remote;

	git_buf_sets(&file_path_buf, cl_git_path_url(cl_fixture("testrepo.git")));

	cl_git_pass(git_repository_new(&inmemory));
	cl_git_pass(git_remote_create_anonymous(&remote, inmemory, git_buf_cstr(&file_path_buf)));
	cl_git_pass(git_remote_connect(remote, GIT_DIRECTION_FETCH, NULL, NULL, NULL));
	cl_assert(git_remote_connected(remote));
	git_remote_disconnect(remote);
	git_remote_free(remote);
	git_repository_free(inmemory);
}