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
typedef  int /*<<< orphan*/  git_odb ;
struct TYPE_2__ {int /*<<< orphan*/  exists_calls; } ;

/* Variables and functions */
 int /*<<< orphan*/  _existing_oid ; 
 TYPE_1__* _fake ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_odb__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_odb_backend_nonrefreshing__exists_is_invoked_once_on_success(void)
{
	git_odb *odb;

	cl_git_pass(git_repository_odb__weakptr(&odb, _repo));
	cl_assert_equal_b(true, git_odb_exists(odb, &_existing_oid));

	cl_assert_equal_i(1, _fake->exists_calls);
}