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
typedef  int /*<<< orphan*/  git_submodule ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_at_line (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  cl_git_report_failure (int,int /*<<< orphan*/ ,char const*,int,char const*) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 int git_submodule_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 

void assert__submodule_exists(
	git_repository *repo, const char *name,
	const char *msg, const char *file, int line)
{
	git_submodule *sm;
	int error = git_submodule_lookup(&sm, repo, name);
	if (error)
		cl_git_report_failure(error, 0, file, line, msg);
	cl_assert_at_line(sm != NULL, file, line);
	git_submodule_free(sm);
}