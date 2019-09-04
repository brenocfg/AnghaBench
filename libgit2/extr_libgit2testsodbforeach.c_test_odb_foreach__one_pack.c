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
typedef  int /*<<< orphan*/  git_odb_backend ;

/* Variables and functions */
 int /*<<< orphan*/  _odb ; 
 int /*<<< orphan*/ * _repo ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  foreach_cb ; 
 int /*<<< orphan*/  git_odb_add_backend (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_odb_backend_one_pack (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  git_odb_new (int /*<<< orphan*/ *) ; 

void test_odb_foreach__one_pack(void)
{
	git_odb_backend *backend = NULL;
	int nobj = 0;

	cl_git_pass(git_odb_new(&_odb));
	cl_git_pass(git_odb_backend_one_pack(&backend, cl_fixture("testrepo.git/objects/pack/pack-a81e489679b7d3418f9ab594bda8ceb37dd4c695.idx")));
	cl_git_pass(git_odb_add_backend(_odb, backend, 1));
	_repo = NULL;

	cl_git_pass(git_odb_foreach(_odb, foreach_cb, &nobj));
	cl_assert(nobj == 1628);
}