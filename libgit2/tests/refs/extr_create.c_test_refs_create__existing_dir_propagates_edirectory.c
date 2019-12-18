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
 int /*<<< orphan*/  GIT_EDIRECTORY ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_master_tip ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 

void test_refs_create__existing_dir_propagates_edirectory(void)
{
	git_reference *new_reference, *fail_reference;
	git_oid id;
	const char *dir_head = "refs/heads/new-dir/new-head",
		*fail_head = "refs/heads/new-dir";

	git_oid_fromstr(&id, current_master_tip);

	/* Create and write the new object id reference */
	cl_git_pass(git_reference_create(&new_reference, g_repo, dir_head, &id, 1, NULL));
	cl_git_fail_with(GIT_EDIRECTORY,
		git_reference_create(&fail_reference, g_repo, fail_head, &id, false, NULL));

	git_reference_free(new_reference);
}