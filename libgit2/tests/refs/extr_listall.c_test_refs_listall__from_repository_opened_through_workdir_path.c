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
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_fixture_sandbox (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ensure_no_refname_starts_with_a_forward_slash (char*) ; 
 int /*<<< orphan*/  p_rename (char*,char*) ; 

void test_refs_listall__from_repository_opened_through_workdir_path(void)
{
	cl_fixture_sandbox("status");
	cl_git_pass(p_rename("status/.gitted", "status/.git"));

	ensure_no_refname_starts_with_a_forward_slash("status");

	cl_fixture_cleanup("status");
}