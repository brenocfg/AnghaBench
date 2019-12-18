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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_reflog_check_entry (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_set_target (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

void test_refs_reflog_messages__updating_a_direct_reference(void)
{
	git_reference *ref, *ref_out, *target_ref;
	git_oid target_id;
	const char *message = "You've been logged, mate!";

	git_reference_name_to_id(&target_id, g_repo, "refs/heads/haacked");
	cl_git_pass(git_reference_lookup(&target_ref, g_repo, "refs/heads/haacked"));

	cl_git_pass(git_reference_lookup(&ref, g_repo, "refs/heads/master"));

	cl_git_pass(git_reference_set_target(&ref_out, ref, &target_id, message));

	cl_reflog_check_entry(g_repo, "refs/heads/master", 0,
		"a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
		"258f0e2a959a364e40ed6603d5d44fbb24765b10",
		NULL, message);

	git_reference_free(target_ref);
	git_reference_free(ref);
	git_reference_free(ref_out);
}