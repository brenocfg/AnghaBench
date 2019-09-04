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
 int /*<<< orphan*/  _remote_url ; 
 int /*<<< orphan*/  _remote_user ; 
 int /*<<< orphan*/  cl_git_fail_with (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cred_failure_cb ; 
 TYPE_3__ g_options ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__strdup (char*) ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_3__*) ; 

void test_online_clone__cred_callback_failure_return_code_is_tunnelled(void)
{
	git__free(_remote_url);
	git__free(_remote_user);

	_remote_url = git__strdup("https://github.com/libgit2/non-existent");
	_remote_user = git__strdup("libgit2test");

	g_options.fetch_opts.callbacks.credentials = cred_failure_cb;

	cl_git_fail_with(-172, git_clone(&g_repo, _remote_url, "./foo", &g_options));
}