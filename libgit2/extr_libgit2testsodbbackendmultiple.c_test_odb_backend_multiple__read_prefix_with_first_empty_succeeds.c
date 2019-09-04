#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_odb_backend ;
typedef  int /*<<< orphan*/  git_odb ;
struct TYPE_4__ {int /*<<< orphan*/  read_prefix_calls; } ;
struct TYPE_3__ {int /*<<< orphan*/  read_prefix_calls; } ;

/* Variables and functions */
 int /*<<< orphan*/  _existing_oid ; 
 TYPE_2__* _fake_empty ; 
 TYPE_1__* _fake_filled ; 
 int /*<<< orphan*/  _obj ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_add_backend (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_odb_read_prefix (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_repository_odb__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_odb_backend_multiple__read_prefix_with_first_empty_succeeds(void)
{
	git_odb *odb;

	cl_git_pass(git_repository_odb__weakptr(&odb, _repo));
	cl_git_pass(git_odb_add_backend(odb, (git_odb_backend *)_fake_filled, 10));
	cl_git_pass(git_odb_add_backend(odb, (git_odb_backend *)_fake_empty, 50));

	cl_git_pass(git_odb_read_prefix(&_obj, odb, &_existing_oid, 7));

	cl_assert_equal_i(1, _fake_filled->read_prefix_calls);
	cl_assert_equal_i(1, _fake_empty->read_prefix_calls);
}