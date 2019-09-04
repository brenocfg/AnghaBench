#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_remote ;
struct TYPE_2__ {scalar_t__ klass; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 scalar_t__ GIT_ERROR_CONFIG ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* git_error_last () ; 
 int /*<<< orphan*/  git_remote_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 

void test_network_remote_remotes__error_when_not_found(void)
{
	git_remote *r;
	cl_git_fail_with(git_remote_lookup(&r, _repo, "does-not-exist"), GIT_ENOTFOUND);

	cl_assert(git_error_last() != NULL);
	cl_assert(git_error_last()->klass == GIT_ERROR_CONFIG);
}