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

/* Variables and functions */
 int /*<<< orphan*/  _odb ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  foreach_cb ; 
 int /*<<< orphan*/  git_odb_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  git_repository_odb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void test_odb_foreach__foreach(void)
{
	int nobj = 0;

	cl_git_pass(git_repository_open(&_repo, cl_fixture("testrepo.git")));
	git_repository_odb(&_odb, _repo);

	cl_git_pass(git_odb_foreach(_odb, foreach_cb, &nobj));
	cl_assert_equal_i(60 + 1640, nobj); /* count + in-pack */
}