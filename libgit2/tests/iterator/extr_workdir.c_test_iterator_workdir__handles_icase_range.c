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
 int /*<<< orphan*/  check_wd_first_through_third_range (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_remove_placeholders (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 

void test_iterator_workdir__handles_icase_range(void)
{
	g_repo = cl_git_sandbox_init("empty_standard_repo");
	cl_git_remove_placeholders(git_repository_path(g_repo), "dummy-marker.txt");

	cl_git_mkfile("empty_standard_repo/before", "whatever\n");
	cl_git_mkfile("empty_standard_repo/FIRST", "whatever\n");
	cl_git_mkfile("empty_standard_repo/second", "whatever\n");
	cl_git_mkfile("empty_standard_repo/THIRD", "whatever\n");
	cl_git_mkfile("empty_standard_repo/zafter", "whatever\n");
	cl_git_mkfile("empty_standard_repo/Zlast", "whatever\n");

	check_wd_first_through_third_range(g_repo, "first", "third");
	check_wd_first_through_third_range(g_repo, "FIRST", "THIRD");
	check_wd_first_through_third_range(g_repo, "first", "THIRD");
	check_wd_first_through_third_range(g_repo, "FIRST", "third");
	check_wd_first_through_third_range(g_repo, "FirSt", "tHiRd");
}