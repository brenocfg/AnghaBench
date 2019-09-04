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
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int /*<<< orphan*/ * _cl_repo ; 
 char const* _cl_sandbox ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char const*,int) ; 

git_repository *cl_git_sandbox_init_new(const char *sandbox)
{
	cl_git_pass(git_repository_init(&_cl_repo, sandbox, false));
	_cl_sandbox = sandbox;

	return _cl_repo;
}