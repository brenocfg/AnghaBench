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
 int GIT_EEXISTS ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  current_head_target ; 
 int /*<<< orphan*/  current_master_tip ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int git_reference_symbolic_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void test_refs_create__propagate_eexists(void)
{
	int error;
	git_oid oid;
	git_reference *ref;

	/* Make sure it works for oid and for symbolic both */
	git_oid_fromstr(&oid, current_master_tip);
	error = git_reference_create(&ref, g_repo, current_head_target, &oid, false, NULL);
	cl_assert(error == GIT_EEXISTS);

	error = git_reference_symbolic_create(&ref, g_repo, "HEAD", current_head_target, false, NULL);
	cl_assert(error == GIT_EEXISTS);
}