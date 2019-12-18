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
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gitno__match_host (char*,char*) ; 

void test_network_matchhost__match(void)
{
	cl_git_pass(gitno__match_host("*.example.org", "www.example.org"));
	cl_git_pass(gitno__match_host("*.foo.example.org", "www.foo.example.org"));
	cl_git_fail(gitno__match_host("*.foo.example.org", "foo.example.org"));
	cl_git_fail(gitno__match_host("*.foo.example.org", "www.example.org"));
	cl_git_fail(gitno__match_host("*.example.org", "example.org"));
	cl_git_fail(gitno__match_host("*.example.org", "www.foo.example.org"));
	cl_git_fail(gitno__match_host("*.example.org", "blah.www.www.example.org"));
}