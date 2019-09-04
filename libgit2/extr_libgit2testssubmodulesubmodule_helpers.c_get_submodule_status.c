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
 int /*<<< orphan*/  GIT_SUBMODULE_IGNORE_UNSPECIFIED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_submodule_status (unsigned int*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

unsigned int get_submodule_status(git_repository *repo, const char *name)
{
	unsigned int status = 0;

	assert(repo && name);

	cl_git_pass(git_submodule_status(&status, repo, name, GIT_SUBMODULE_IGNORE_UNSPECIFIED));

	return status;
}