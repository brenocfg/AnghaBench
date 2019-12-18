#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {TYPE_1__ member_0; } ;
typedef  TYPE_2__ git_oid ;
typedef  int /*<<< orphan*/  git_odb_object ;
struct TYPE_10__ {char* member_0; char* member_1; } ;
typedef  TYPE_3__ fake_object ;
struct TYPE_11__ {int /*<<< orphan*/  message; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_OPT_ENABLE_STRICT_HASH_VERIFICATION ; 
 int /*<<< orphan*/  _odb ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_7__* git_error_last () ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_exists (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  git_odb_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  setup_backend (TYPE_3__ const*) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 

void test_odb_backend_simple__null_oid_is_ignored(void)
{
	const fake_object objs[] = {
		{ "0000000000000000000000000000000000000000", "null oid content" },
		{ NULL, NULL }
	};
	git_oid null_oid = {{0}};
	git_odb_object *obj;

	setup_backend(objs);

	cl_git_pass(git_libgit2_opts(GIT_OPT_ENABLE_STRICT_HASH_VERIFICATION, 0));
	cl_assert(!git_odb_exists(_odb, &null_oid));

	cl_git_fail_with(GIT_ENOTFOUND, git_odb_read(&obj, _odb, &null_oid));
	cl_assert(git_error_last() && strstr(git_error_last()->message, "null OID"));
}