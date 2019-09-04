#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_2__ {int /*<<< orphan*/  message; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 TYPE_1__* git_error_last () ; 
 int /*<<< orphan*/  git_reference_dwim (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 

void test_refs_lookup__dwim_notfound(void)
{
	git_reference *ref;

	cl_git_fail_with(GIT_ENOTFOUND, git_reference_dwim(&ref, g_repo, "idontexist"));
	cl_assert_equal_s("no reference found for shorthand 'idontexist'", git_error_last()->message);
}