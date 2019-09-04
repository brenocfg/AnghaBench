#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* member_0; char* member_1; int /*<<< orphan*/  oid; } ;
typedef  TYPE_1__ fake_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_EAMBIGUOUS ; 
 int /*<<< orphan*/  _obj ; 
 int /*<<< orphan*/  _odb ; 
 int /*<<< orphan*/  _oid ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_read_prefix (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_backend (TYPE_1__ const*) ; 

void test_odb_backend_simple__read_with_ambiguous_prefix_fails(void)
{
	const fake_object objs[] = {
		{ "1234567890111111111111111111111111111111", "first content" },
		{ "1234567890222222222222222222222222222222", "second content" },
		{ NULL, NULL }
	};

	setup_backend(objs);

	cl_git_pass(git_oid_fromstr(&_oid, objs[0].oid));
	cl_git_fail_with(GIT_EAMBIGUOUS, git_odb_read_prefix(&_obj, _odb, &_oid, 7));
}