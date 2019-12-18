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
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  _refspec ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_refspec_rtransform (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 

void test_network_remote_remotes__transform_destination_to_source(void)
{
	git_buf ref = GIT_BUF_INIT;

	cl_git_pass(git_refspec_rtransform(&ref, _refspec, "refs/remotes/test/master"));
	cl_assert_equal_s(ref.ptr, "refs/heads/master");
	git_buf_dispose(&ref);
}