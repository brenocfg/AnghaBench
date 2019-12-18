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

/* Variables and functions */
 int /*<<< orphan*/  _dummy ; 
 int /*<<< orphan*/  _remote ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_fixture_sandbox (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_path_url (char*) ; 
 int /*<<< orphan*/  git_remote_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ *,char*) ; 

void test_network_remote_push__initialize(void)
{
	cl_fixture_sandbox("testrepo.git");
	git_repository_open(&_repo, "testrepo.git");

	/* We need a repository to have a remote */
	cl_git_pass(git_repository_init(&_dummy, "dummy.git", true));
	cl_git_pass(git_remote_create(&_remote, _dummy, "origin", cl_git_path_url("testrepo.git")));
}