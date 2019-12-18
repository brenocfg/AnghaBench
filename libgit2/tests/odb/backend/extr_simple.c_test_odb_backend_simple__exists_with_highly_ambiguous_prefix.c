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
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_3__ {char* member_0; char* member_1; int /*<<< orphan*/  oid; } ;
typedef  TYPE_1__ fake_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_EAMBIGUOUS ; 
 int /*<<< orphan*/  GIT_OPT_ENABLE_STRICT_HASH_VERIFICATION ; 
 int /*<<< orphan*/  _odb ; 
 int /*<<< orphan*/  _oid ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_exists_prefix (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_oid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_backend (TYPE_1__ const*) ; 

void test_odb_backend_simple__exists_with_highly_ambiguous_prefix(void)
{
	const fake_object objs[] = {
		{ "1234567890111111111111111111111111111111", "first content" },
		{ "1234567890111111111111111111111111111112", "second content" },
		{ NULL, NULL }
	};
	git_oid found;

	setup_backend(objs);

	cl_git_pass(git_oid_fromstr(&_oid, objs[0].oid));
	cl_git_pass(git_libgit2_opts(GIT_OPT_ENABLE_STRICT_HASH_VERIFICATION, 0));
	cl_git_fail_with(GIT_EAMBIGUOUS, git_odb_exists_prefix(&found, _odb, &_oid, 39));
	cl_git_pass(git_odb_exists_prefix(&found, _odb, &_oid, 40));
	cl_assert(git_oid_equal(&found, &_oid));
}