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
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_mempack_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_odb_add_backend (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_odb_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_wrap_odb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void test_odb_backend_mempack__initialize(void)
{
	git_odb_backend *backend;

	cl_git_pass(git_mempack_new(&backend));
	cl_git_pass(git_odb_new(&_odb));
	cl_git_pass(git_odb_add_backend(_odb, backend, 10));
	cl_git_pass(git_repository_wrap_odb(&_repo, _odb));
}