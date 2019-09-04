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
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_2__ {int /*<<< orphan*/  read_calls; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 TYPE_1__* _fake ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 

void test_odb_backend_nonrefreshing__read_is_invoked_once_when_revparsing_a_full_oid(void)
{
	git_object *obj;

	cl_git_fail_with(
		git_revparse_single(&obj, _repo, "deadbeefdeadbeefdeadbeefdeadbeefdeadbeef"),
		GIT_ENOTFOUND);

	cl_assert_equal_i(1, _fake->read_calls);
}