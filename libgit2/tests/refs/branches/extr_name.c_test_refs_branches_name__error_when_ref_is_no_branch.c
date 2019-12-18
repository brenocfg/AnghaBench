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
 int /*<<< orphan*/  git_branch_name (char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ref ; 
 int /*<<< orphan*/  repo ; 

void test_refs_branches_name__error_when_ref_is_no_branch(void)
{
	const char *name;

	cl_git_pass(git_reference_lookup(&ref,repo,"refs/notes/fanout"));
	cl_git_fail(git_branch_name(&name,ref));
}