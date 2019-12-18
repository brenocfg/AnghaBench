#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char** member_0; int member_1; char** strings; } ;
typedef  TYPE_3__ git_strarray ;
struct TYPE_6__ {int /*<<< orphan*/ * certificate_check; TYPE_3__* payload; int /*<<< orphan*/  credentials; int /*<<< orphan*/  transport; } ;
struct TYPE_7__ {TYPE_1__ callbacks; } ;
struct TYPE_9__ {TYPE_2__ fetch_opts; int /*<<< orphan*/  remote_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  _remote_url ; 
 int /*<<< orphan*/  _remote_user ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clar__skip () ; 
 int /*<<< orphan*/  cred_cb ; 
 int /*<<< orphan*/  custom_remote_ssh_with_paths ; 
 TYPE_4__ g_options ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  git_transport_ssh_with_paths ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

void test_online_clone__ssh_with_paths(void)
{
	char *bad_paths[] = {
		"/bin/yes",
		"/bin/false",
	};
	char *good_paths[] = {
		"/usr/bin/git-upload-pack",
		"/usr/bin/git-receive-pack",
	};
	git_strarray arr = {
		bad_paths,
		2,
	};

#ifndef GIT_SSH
	clar__skip();
#endif
	if (!_remote_url || !_remote_user || strncmp(_remote_url, "ssh://", 5) != 0)
		clar__skip();

	g_options.remote_cb = custom_remote_ssh_with_paths;
	g_options.fetch_opts.callbacks.transport = git_transport_ssh_with_paths;
	g_options.fetch_opts.callbacks.credentials = cred_cb;
	g_options.fetch_opts.callbacks.payload = &arr;
	g_options.fetch_opts.callbacks.certificate_check = NULL;

	cl_git_fail(git_clone(&g_repo, _remote_url, "./foo", &g_options));

	arr.strings = good_paths;
	cl_git_pass(git_clone(&g_repo, _remote_url, "./foo", &g_options));
}