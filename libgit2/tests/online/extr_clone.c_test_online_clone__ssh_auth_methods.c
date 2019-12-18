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
struct TYPE_5__ {int* payload; int /*<<< orphan*/ * certificate_check; int /*<<< orphan*/  credentials; } ;
struct TYPE_6__ {TYPE_1__ callbacks; } ;
struct TYPE_7__ {TYPE_2__ fetch_opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_EUSER ; 
 char* SSH_REPO_URL ; 
 int /*<<< orphan*/  check_ssh_auth_methods ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clar__skip () ; 
 TYPE_3__ g_options ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ *,char*,char*,TYPE_3__*) ; 

void test_online_clone__ssh_auth_methods(void)
{
	int with_user;

#ifndef GIT_SSH
	clar__skip();
#endif
	g_options.fetch_opts.callbacks.credentials = check_ssh_auth_methods;
	g_options.fetch_opts.callbacks.payload = &with_user;
	g_options.fetch_opts.callbacks.certificate_check = NULL;

	with_user = 0;
	cl_git_fail_with(GIT_EUSER,
		git_clone(&g_repo, SSH_REPO_URL, "./foo", &g_options));

	with_user = 1;
	cl_git_fail_with(GIT_EUSER,
		git_clone(&g_repo, "ssh://git@github.com/libgit2/TestGitRepository", "./foo", &g_options));
}