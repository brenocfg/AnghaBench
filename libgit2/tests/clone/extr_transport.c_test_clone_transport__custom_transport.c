#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_6__ {int* payload; int /*<<< orphan*/  transport; } ;
struct TYPE_7__ {TYPE_1__ callbacks; } ;
struct TYPE_8__ {TYPE_2__ fetch_opts; int /*<<< orphan*/  remote_cb; } ;
typedef  TYPE_3__ git_clone_options ;

/* Variables and functions */
 TYPE_3__ GIT_CLONE_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  custom_transport ; 
 int /*<<< orphan*/  custom_transport_remote_create ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 

void test_clone_transport__custom_transport(void)
{
	git_repository *repo;
	git_clone_options clone_opts = GIT_CLONE_OPTIONS_INIT;
	int custom_transport_used = 0;

	clone_opts.remote_cb = custom_transport_remote_create;
	clone_opts.fetch_opts.callbacks.transport = custom_transport;
	clone_opts.fetch_opts.callbacks.payload = &custom_transport_used;

	cl_git_pass(git_clone(&repo, cl_fixture("testrepo.git"), "./custom_transport.git", &clone_opts));
	git_repository_free(repo);

	cl_git_pass(git_futils_rmdir_r("./custom_transport.git", NULL, GIT_RMDIR_REMOVE_FILES));

	cl_assert(custom_transport_used == 1);
}