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
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_reflog_check_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_rename (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int,char*) ; 

void test_refs_reflog_messages__renaming_ref(void)
{
	git_reference *ref, *new_ref;

	cl_git_pass(git_reference_lookup(&ref, g_repo, "refs/heads/master"));
	cl_git_pass(git_reference_rename(&new_ref, ref, "refs/heads/renamed", false,
									 "message"));

	cl_reflog_check_entry(g_repo, git_reference_name(new_ref), 0,
		"a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
		"a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
		"foo@example.com", "message");

	git_reference_free(ref);
	git_reference_free(new_ref);
}