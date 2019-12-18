#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  resolve_url; } ;
typedef  TYPE_1__ git_remote_callbacks ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_DIRECTION_FETCH ; 
 int /*<<< orphan*/  GIT_DIRECTION_PUSH ; 
 TYPE_1__ GIT_REMOTE_CALLBACKS_INIT ; 
 int /*<<< orphan*/  _remote ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_remote__urlfordirection (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_remote_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_remote_pushurl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_url (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  urlresolve_passthrough_callback ; 

void test_network_remote_remotes__urlresolve_passthrough(void)
{
	git_buf url = GIT_BUF_INIT;
	const char *orig_url = "git://github.com/libgit2/libgit2";

	git_remote_callbacks callbacks = GIT_REMOTE_CALLBACKS_INIT;
	callbacks.resolve_url = urlresolve_passthrough_callback;

	cl_assert_equal_s(git_remote_name(_remote), "test");
	cl_assert_equal_s(git_remote_url(_remote), orig_url);
	cl_assert(git_remote_pushurl(_remote) == NULL);

	cl_git_pass(git_remote__urlfordirection(&url, _remote, GIT_DIRECTION_FETCH, &callbacks));
	cl_assert_equal_s(url.ptr, orig_url);

	cl_git_pass(git_remote__urlfordirection(&url, _remote, GIT_DIRECTION_PUSH, &callbacks));
	cl_assert_equal_s(url.ptr, orig_url);

	git_buf_dispose(&url);
}