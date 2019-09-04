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
typedef  int /*<<< orphan*/  git_remote ;
struct TYPE_5__ {size_t* payload; int /*<<< orphan*/  transfer_progress; } ;
struct TYPE_6__ {TYPE_1__ callbacks; } ;
typedef  TYPE_2__ git_fetch_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIRECTION_FETCH ; 
 TYPE_2__ GIT_FETCH_OPTIONS_INIT ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cancel_at_half ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  git_remote_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_download (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 

void test_online_fetch__can_cancel(void)
{
	git_remote *remote;
	size_t bytes_received = 0;
	git_fetch_options options = GIT_FETCH_OPTIONS_INIT;

	cl_git_pass(git_remote_create(&remote, _repo, "test",
				"http://github.com/libgit2/TestGitRepository.git"));

	options.callbacks.transfer_progress = cancel_at_half;
	options.callbacks.payload = &bytes_received;

	cl_git_pass(git_remote_connect(remote, GIT_DIRECTION_FETCH, NULL, NULL, NULL));
	cl_git_fail_with(git_remote_download(remote, NULL, &options), -4321);
	git_remote_disconnect(remote);
	git_remote_free(remote);
}