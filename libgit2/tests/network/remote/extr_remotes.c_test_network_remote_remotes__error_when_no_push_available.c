#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {char** member_0; int member_1; } ;
typedef  TYPE_2__ git_strarray ;
struct TYPE_14__ {int /*<<< orphan*/  transport; } ;
typedef  TYPE_3__ git_remote_callbacks ;
struct TYPE_15__ {TYPE_1__* transport; } ;
typedef  TYPE_4__ git_remote ;
struct TYPE_12__ {int /*<<< orphan*/ * push; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIRECTION_PUSH ; 
 TYPE_3__ GIT_REMOTE_CALLBACKS_INIT ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_fail_with (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_connect (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_create_anonymous (TYPE_4__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_free (TYPE_4__*) ; 
 int /*<<< orphan*/  git_remote_upload (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_transport_local ; 

void test_network_remote_remotes__error_when_no_push_available(void)
{
	git_remote *r;
	git_remote_callbacks callbacks = GIT_REMOTE_CALLBACKS_INIT;
	char *specs = {
		"refs/heads/master",
	};
	git_strarray arr = {
		&specs,
		1,
	};


	cl_git_pass(git_remote_create_anonymous(&r, _repo, cl_fixture("testrepo.git")));

	callbacks.transport = git_transport_local;
	cl_git_pass(git_remote_connect(r, GIT_DIRECTION_PUSH, &callbacks, NULL, NULL));

	/* Make sure that push is really not available */
	r->transport->push = NULL;

	cl_git_fail_with(-1, git_remote_upload(r, &arr, NULL));

	git_remote_free(r);
}