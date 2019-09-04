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
typedef  int /*<<< orphan*/  fake_backend ;

/* Variables and functions */
 int /*<<< orphan*/  EXISTING_HASH ; 
 int /*<<< orphan*/  _existing_oid ; 
 int /*<<< orphan*/ * _fake_empty ; 
 int /*<<< orphan*/ * _fake_filled ; 
 int /*<<< orphan*/ * _obj ; 
 int /*<<< orphan*/  _objects_empty ; 
 int /*<<< orphan*/  _objects_filled ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  build_fake_backend (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void test_odb_backend_multiple__initialize(void)
{
	git_odb_backend *backend;

	git_oid_fromstr(&_existing_oid, EXISTING_HASH);

	_obj = NULL;
	_repo = cl_git_sandbox_init("testrepo.git");

	cl_git_pass(build_fake_backend(&backend, _objects_filled));
	_fake_filled = (fake_backend *)backend;

	cl_git_pass(build_fake_backend(&backend, _objects_empty));
	_fake_empty = (fake_backend *)backend;
}