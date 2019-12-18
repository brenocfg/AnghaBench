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
 int /*<<< orphan*/  cl_assert_equal_i (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  cl_git_pass (unsigned int) ; 
 unsigned int git_status_file (unsigned int*,int /*<<< orphan*/ *,char const*) ; 

void assert_status(
	git_repository *repo,
	const char *path,
	int status_flags)
{
	unsigned int status;

	if (status_flags < 0)
		cl_assert_equal_i(status_flags, git_status_file(&status, repo, path));
	else {
		cl_git_pass(git_status_file(&status, repo, path));
		cl_assert_equal_i((unsigned int)status_flags, status);
	}
}