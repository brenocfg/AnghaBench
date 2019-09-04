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
struct TYPE_3__ {int /*<<< orphan*/  exec; int /*<<< orphan*/  id; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ git_rebase_operation ;
typedef  int /*<<< orphan*/  git_rebase ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 size_t GIT_REBASE_OPERATION_PICK ; 
 int /*<<< orphan*/  cl_assert_equal_i (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* git_rebase_operation_byindex (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_rebase_operation_current (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_rebase_operation_entrycount (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_operations(git_rebase *rebase, size_t expected_current)
{
	size_t i, expected_count = 5;
	git_oid expected_oid[5];
	git_rebase_operation *operation;

	git_oid_fromstr(&expected_oid[0], "da9c51a23d02d931a486f45ad18cda05cf5d2b94");
	git_oid_fromstr(&expected_oid[1], "8d1f13f93c4995760ac07d129246ac1ff64c0be9");
	git_oid_fromstr(&expected_oid[2], "3069cc907e6294623e5917ef6de663928c1febfb");
	git_oid_fromstr(&expected_oid[3], "588e5d2f04d49707fe4aab865e1deacaf7ef6787");
	git_oid_fromstr(&expected_oid[4], "b146bd7608eac53d9bf9e1a6963543588b555c64");

	cl_assert_equal_i(expected_count, git_rebase_operation_entrycount(rebase));
	cl_assert_equal_i(expected_current, git_rebase_operation_current(rebase));

	for (i = 0; i < expected_count; i++) {
		operation = git_rebase_operation_byindex(rebase, i);
		cl_assert_equal_i(GIT_REBASE_OPERATION_PICK, operation->type);
		cl_assert_equal_oid(&expected_oid[i], &operation->id);
		cl_assert_equal_p(NULL, operation->exec);
	}
}