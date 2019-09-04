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
 int /*<<< orphan*/  GIT_FILTER_DRIVER_PRIORITY ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  create_wildcard_filter () ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_filter_register (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_filter_wildcard__initialize(void)
{
	cl_git_pass(git_filter_register(
		"wildcard", create_wildcard_filter(), GIT_FILTER_DRIVER_PRIORITY));

	g_repo = cl_git_sandbox_init("empty_standard_repo");

	cl_git_rewritefile(
		"empty_standard_repo/.gitattributes",
		"* binary\n"
		"hero-flip-* filter=wcflip\n"
		"hero-reverse-* filter=wcreverse\n"
		"none-* filter=unregistered\n");
}