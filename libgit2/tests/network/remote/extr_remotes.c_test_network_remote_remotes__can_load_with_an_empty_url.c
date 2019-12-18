#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * pushurl; int /*<<< orphan*/ * url; } ;
typedef  TYPE_1__ git_remote ;
struct TYPE_7__ {scalar_t__ klass; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIRECTION_FETCH ; 
 scalar_t__ GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_5__* git_error_last () ; 
 int /*<<< orphan*/  git_remote_connect (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_remote_lookup (TYPE_1__**,int /*<<< orphan*/ ,char*) ; 

void test_network_remote_remotes__can_load_with_an_empty_url(void)
{
	git_remote *remote = NULL;

	cl_git_pass(git_remote_lookup(&remote, _repo, "empty-remote-url"));

	cl_assert(remote->url == NULL);
	cl_assert(remote->pushurl == NULL);

	cl_git_fail(git_remote_connect(remote, GIT_DIRECTION_FETCH, NULL, NULL, NULL));

	cl_assert(git_error_last() != NULL);
	cl_assert(git_error_last()->klass == GIT_ERROR_INVALID);

	git_remote_free(remote);
}