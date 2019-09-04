#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  credentials; } ;
struct TYPE_6__ {TYPE_1__ callbacks; } ;
struct TYPE_7__ {TYPE_2__ fetch_opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  _remote_ssh_privkey ; 
 int /*<<< orphan*/  _remote_url ; 
 int /*<<< orphan*/  _remote_user ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clar__skip () ; 
 TYPE_3__ g_options ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  ssh_memory_cred_cb ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

void test_online_clone__ssh_memory_auth(void)
{
#ifndef GIT_SSH_MEMORY_CREDENTIALS
	clar__skip();
#endif
	if (!_remote_url || !_remote_user || !_remote_ssh_privkey || strncmp(_remote_url, "ssh://", 5) != 0)
		clar__skip();

	g_options.fetch_opts.callbacks.credentials = ssh_memory_cred_cb;

	cl_git_pass(git_clone(&g_repo, _remote_url, "./foo", &g_options));
}