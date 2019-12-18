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
typedef  int /*<<< orphan*/  git_odb ;
typedef  int /*<<< orphan*/  fake_backend ;

/* Variables and functions */
 int /*<<< orphan*/ * _fake ; 
 int /*<<< orphan*/  _objects ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  build_fake_backend (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_odb_add_backend (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_repository_odb__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_repository_and_backend(void)
{
	git_odb *odb = NULL;
	git_odb_backend *backend = NULL;

	_repo = cl_git_sandbox_init("testrepo.git");

	cl_git_pass(build_fake_backend(&backend, _objects));

	cl_git_pass(git_repository_odb__weakptr(&odb, _repo));
	cl_git_pass(git_odb_add_backend(odb, backend, 10));

	_fake = (fake_backend *)backend;
}