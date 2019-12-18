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
struct TYPE_2__ {int /*<<< orphan*/  read_prefix_calls; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 TYPE_1__* _fake ; 
 int /*<<< orphan*/  _nonexisting_oid ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_lookup_prefix (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void test_odb_backend_nonrefreshing__readprefix_is_invoked_once_on_failure(void)
{
	git_object *obj;

	cl_git_fail_with(
		git_object_lookup_prefix(&obj, _repo, &_nonexisting_oid, 7, GIT_OBJECT_ANY),
		GIT_ENOTFOUND);

	cl_assert_equal_i(1, _fake->read_prefix_calls);
}