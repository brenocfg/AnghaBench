#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_4__ {int /*<<< orphan*/  remote_cb; } ;
typedef  TYPE_1__ git_clone_options ;

/* Variables and functions */
 TYPE_1__ GIT_CLONE_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  URL ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  remote_single_branch ; 

void test_online_remotes__restricted_refspecs(void)
{
	git_clone_options opts = GIT_CLONE_OPTIONS_INIT;
	git_repository *repo;

	opts.remote_cb = remote_single_branch;

	cl_git_fail_with(GIT_EINVALIDSPEC, git_clone(&repo, URL, "./restrict-refspec", &opts));
}