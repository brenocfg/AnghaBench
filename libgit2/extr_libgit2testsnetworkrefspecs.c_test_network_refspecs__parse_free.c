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
typedef  int /*<<< orphan*/  git_refspec ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_refspec_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_refspec_parse (int /*<<< orphan*/ **,char*,int) ; 

void test_network_refspecs__parse_free(void)
{
	git_refspec *spec = NULL;

	cl_git_fail(git_refspec_parse(&spec, "", 0));
	cl_git_fail(git_refspec_parse(&spec, ":::", 0));
	cl_git_pass(git_refspec_parse(&spec, "HEAD:", 1));

	cl_assert(spec != NULL);
	git_refspec_free(spec);
}