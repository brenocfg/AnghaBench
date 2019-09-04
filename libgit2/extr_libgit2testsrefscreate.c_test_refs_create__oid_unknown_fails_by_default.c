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
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*) ; 

void test_refs_create__oid_unknown_fails_by_default(void)
{
	git_reference *new_reference, *looked_up_ref;
	git_oid id;

	const char *new_head = "refs/heads/new-head";

	git_oid_fromstr(&id, "deadbeef3f795b2b4353bcce3a527ad0a4f7f644");

	/* Create and write the new object id reference */
	cl_git_fail(git_reference_create(&new_reference, g_repo, new_head, &id, 0, NULL));

	/* Ensure the reference can't be looked-up... */
	cl_git_fail(git_reference_lookup(&looked_up_ref, g_repo, new_head));
}