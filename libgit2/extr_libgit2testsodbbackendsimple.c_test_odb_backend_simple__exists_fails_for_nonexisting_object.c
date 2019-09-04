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
struct TYPE_3__ {char* member_0; char* member_1; } ;
typedef  TYPE_1__ fake_object ;

/* Variables and functions */
 int /*<<< orphan*/  _odb ; 
 int /*<<< orphan*/  _oid ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ git_odb_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  setup_backend (TYPE_1__ const*) ; 

void test_odb_backend_simple__exists_fails_for_nonexisting_object(void)
{
	const fake_object objs[] = {
		{ "f6ea0495187600e7b2288c8ac19c5886383a4632", "foobar" },
		{ NULL, NULL }
	};

	setup_backend(objs);

	cl_git_pass(git_oid_fromstr(&_oid, "f6ea0495187600e7b2288c8ac19c5886383a4633"));
	cl_assert(git_odb_exists(_odb, &_oid) == 0);
}