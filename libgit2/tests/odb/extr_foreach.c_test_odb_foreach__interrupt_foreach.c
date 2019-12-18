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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  _odb ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  foreach_stop_cb ; 
 int /*<<< orphan*/  foreach_stop_cb_positive_ret ; 
 int /*<<< orphan*/  foreach_stop_first_cb ; 
 int /*<<< orphan*/  git_odb_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_repository_odb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void test_odb_foreach__interrupt_foreach(void)
{
	int nobj = 0;
	git_oid id;

	cl_git_pass(git_repository_open(&_repo, cl_fixture("testrepo.git")));
	git_repository_odb(&_odb, _repo);

	cl_assert_equal_i(-321, git_odb_foreach(_odb, foreach_stop_cb, &nobj));
	cl_assert(nobj == 1000);

	nobj = 0;

	cl_assert_equal_i(321, git_odb_foreach(_odb, foreach_stop_cb_positive_ret, &nobj));
	cl_assert(nobj == 1000);

	git_odb_free(_odb);
	git_repository_free(_repo);

	cl_git_pass(git_repository_init(&_repo, "onlyloose.git", true));
	git_repository_odb(&_odb, _repo);

	cl_git_pass(git_odb_write(&id, _odb, "", 0, GIT_OBJECT_BLOB));
	cl_assert_equal_i(-123, git_odb_foreach(_odb, foreach_stop_first_cb, &nobj));
}