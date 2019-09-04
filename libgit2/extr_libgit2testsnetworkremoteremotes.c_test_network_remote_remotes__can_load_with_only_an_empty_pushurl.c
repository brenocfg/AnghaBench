#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * pushurl; int /*<<< orphan*/ * url; } ;
typedef  TYPE_1__ git_remote ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIRECTION_FETCH ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_connect (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_remote_lookup (TYPE_1__**,int /*<<< orphan*/ ,char*) ; 

void test_network_remote_remotes__can_load_with_only_an_empty_pushurl(void)
{
	git_remote *remote = NULL;

	cl_git_pass(git_remote_lookup(&remote, _repo, "empty-remote-pushurl"));

	cl_assert(remote->url == NULL);
	cl_assert(remote->pushurl == NULL);

	cl_git_fail(git_remote_connect(remote, GIT_DIRECTION_FETCH, NULL, NULL, NULL));

	git_remote_free(remote);
}