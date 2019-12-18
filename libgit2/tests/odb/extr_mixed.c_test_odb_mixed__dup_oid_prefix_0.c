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
typedef  int /*<<< orphan*/  hex ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_EAMBIGUOUS ; 
 int /*<<< orphan*/  _odb ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_exists_prefix (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_object_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_read_prefix (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstrn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

void test_odb_mixed__dup_oid_prefix_0(void) {
	char hex[10];
	git_oid oid, found;
	git_odb_object *obj;

	/* ambiguous in the same pack file */

	strncpy(hex, "dea509d0", sizeof(hex));
	cl_git_pass(git_oid_fromstrn(&oid, hex, strlen(hex)));
	cl_assert_equal_i(
		GIT_EAMBIGUOUS, git_odb_read_prefix(&obj, _odb, &oid, strlen(hex)));
	cl_assert_equal_i(
		GIT_EAMBIGUOUS, git_odb_exists_prefix(&found, _odb, &oid, strlen(hex)));

	strncpy(hex, "dea509d09", sizeof(hex));
	cl_git_pass(git_oid_fromstrn(&oid, hex, strlen(hex)));
	cl_git_pass(git_odb_read_prefix(&obj, _odb, &oid, strlen(hex)));
	cl_git_pass(git_odb_exists_prefix(&found, _odb, &oid, strlen(hex)));
	cl_assert_equal_oid(&found, git_odb_object_id(obj));
	git_odb_object_free(obj);

	strncpy(hex, "dea509d0b", sizeof(hex));
	cl_git_pass(git_oid_fromstrn(&oid, hex, strlen(hex)));
	cl_git_pass(git_odb_read_prefix(&obj, _odb, &oid, strlen(hex)));
	git_odb_object_free(obj);

	/* ambiguous in different pack files */

	strncpy(hex, "81b5bff5", sizeof(hex));
	cl_git_pass(git_oid_fromstrn(&oid, hex, strlen(hex)));
	cl_assert_equal_i(
		GIT_EAMBIGUOUS, git_odb_read_prefix(&obj, _odb, &oid, strlen(hex)));
	cl_assert_equal_i(
		GIT_EAMBIGUOUS, git_odb_exists_prefix(&found, _odb, &oid, strlen(hex)));

	strncpy(hex, "81b5bff5b", sizeof(hex));
	cl_git_pass(git_oid_fromstrn(&oid, hex, strlen(hex)));
	cl_git_pass(git_odb_read_prefix(&obj, _odb, &oid, strlen(hex)));
	cl_git_pass(git_odb_exists_prefix(&found, _odb, &oid, strlen(hex)));
	cl_assert_equal_oid(&found, git_odb_object_id(obj));
	git_odb_object_free(obj);

	strncpy(hex, "81b5bff5f", sizeof(hex));
	cl_git_pass(git_oid_fromstrn(&oid, hex, strlen(hex)));
	cl_git_pass(git_odb_read_prefix(&obj, _odb, &oid, strlen(hex)));
	git_odb_object_free(obj);

	/* ambiguous in pack file and loose */

	strncpy(hex, "0ddeaded", sizeof(hex));
	cl_git_pass(git_oid_fromstrn(&oid, hex, strlen(hex)));
	cl_assert_equal_i(
		GIT_EAMBIGUOUS, git_odb_read_prefix(&obj, _odb, &oid, strlen(hex)));
	cl_assert_equal_i(
		GIT_EAMBIGUOUS, git_odb_exists_prefix(&found, _odb, &oid, strlen(hex)));

	strncpy(hex, "0ddeaded9", sizeof(hex));
	cl_git_pass(git_oid_fromstrn(&oid, hex, strlen(hex)));
	cl_git_pass(git_odb_read_prefix(&obj, _odb, &oid, strlen(hex)));
	cl_git_pass(git_odb_exists_prefix(&found, _odb, &oid, strlen(hex)));
	cl_assert_equal_oid(&found, git_odb_object_id(obj));
	git_odb_object_free(obj);

	strncpy(hex, "0ddeadede", sizeof(hex));
	cl_git_pass(git_oid_fromstrn(&oid, hex, strlen(hex)));
	cl_git_pass(git_odb_read_prefix(&obj, _odb, &oid, strlen(hex)));
	git_odb_object_free(obj);
}