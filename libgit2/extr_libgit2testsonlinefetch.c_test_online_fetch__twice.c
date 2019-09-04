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
typedef  int /*<<< orphan*/  git_remote ;

/* Variables and functions */
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  git_remote_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 

void test_online_fetch__twice(void)
{
	git_remote *remote;

	cl_git_pass(git_remote_create(&remote, _repo, "test", "http://github.com/libgit2/TestGitRepository.git"));
	cl_git_pass(git_remote_fetch(remote, NULL, NULL, NULL));
	cl_git_pass(git_remote_fetch(remote, NULL, NULL, NULL));

	git_remote_free(remote);
}