#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_object_t ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 int git_object_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_streq (int /*<<< orphan*/ ,char const*) ; 
 int git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  repo ; 

__attribute__((used)) static void assert_object_oid(const char* revision, const char* expected_oid, git_object_t type)
{
	int result;
	git_object *obj;

	result = git_revparse_single(&obj, repo, revision);

	if (!expected_oid) {
		cl_assert_equal_i(GIT_ENOTFOUND, result);
		return;
	} else
		cl_assert_equal_i(0, result);

	cl_git_pass(git_oid_streq(git_object_id(obj), expected_oid));
	cl_assert_equal_i(type, git_object_type(obj));
	git_object_free(obj);
}