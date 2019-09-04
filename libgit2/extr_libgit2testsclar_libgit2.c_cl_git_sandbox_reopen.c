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
 int /*<<< orphan*/  _cl_sandbox ; 
 int /*<<< orphan*/  cl_fixture_basename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

git_repository *cl_git_sandbox_reopen(void)
{
	if (_cl_repo) {
		git_repository_free(_cl_repo);
		_cl_repo = NULL;

		cl_git_pass(git_repository_open(
			&_cl_repo, cl_fixture_basename(_cl_sandbox)));
	}

	return _cl_repo;
}