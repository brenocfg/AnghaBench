#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_filter ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_EEXISTS ; 
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 char* GIT_FILTER_CRLF ; 
 char* GIT_FILTER_IDENT ; 
 int /*<<< orphan*/  GIT_FILTER_VERSION ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_filter_register (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_filter_unregister (char*) ; 

void test_filter_custom__filter_registry_failure_cases(void)
{
	git_filter fake = { GIT_FILTER_VERSION, 0 };

	cl_assert_equal_i(GIT_EEXISTS, git_filter_register("bitflip", &fake, 0));

	cl_git_fail(git_filter_unregister(GIT_FILTER_CRLF));
	cl_git_fail(git_filter_unregister(GIT_FILTER_IDENT));
	cl_assert_equal_i(GIT_ENOTFOUND, git_filter_unregister("not-a-filter"));
}