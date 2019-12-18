#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_reference ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int GIT_REFERENCE_DIRECT ; 
 int GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_head_target ; 
 int /*<<< orphan*/  current_master_tip ; 
 int /*<<< orphan*/ * g_repo ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_reference_lookup (TYPE_1__**,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_reference_resolve (TYPE_1__**,TYPE_1__*) ; 
 int /*<<< orphan*/  git_reference_symbolic_create (TYPE_1__**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_target (TYPE_1__*) ; 
 int git_reference_type (TYPE_1__*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,char*) ; 
 scalar_t__ reference_is_packed (TYPE_1__*) ; 

void test_refs_create__symbolic(void)
{
	/* create a new symbolic reference */
	git_reference *new_reference, *looked_up_ref, *resolved_ref;
	git_repository *repo2;
	git_oid id;

	const char *new_head_tracker = "ANOTHER_HEAD_TRACKER";

	git_oid_fromstr(&id, current_master_tip);

	/* Create and write the new symbolic reference */
	cl_git_pass(git_reference_symbolic_create(&new_reference, g_repo, new_head_tracker, current_head_target, 0, NULL));

	/* Ensure the reference can be looked-up... */
	cl_git_pass(git_reference_lookup(&looked_up_ref, g_repo, new_head_tracker));
	cl_assert(git_reference_type(looked_up_ref) & GIT_REFERENCE_SYMBOLIC);
	cl_assert(reference_is_packed(looked_up_ref) == 0);
	cl_assert_equal_s(looked_up_ref->name, new_head_tracker);

	/* ...peeled.. */
	cl_git_pass(git_reference_resolve(&resolved_ref, looked_up_ref));
	cl_assert(git_reference_type(resolved_ref) == GIT_REFERENCE_DIRECT);

	/* ...and that it points to the current master tip */
	cl_assert_equal_oid(&id, git_reference_target(resolved_ref));
	git_reference_free(looked_up_ref);
	git_reference_free(resolved_ref);

	/* Similar test with a fresh new repository */
	cl_git_pass(git_repository_open(&repo2, "testrepo"));

	cl_git_pass(git_reference_lookup(&looked_up_ref, repo2, new_head_tracker));
	cl_git_pass(git_reference_resolve(&resolved_ref, looked_up_ref));
	cl_assert_equal_oid(&id, git_reference_target(resolved_ref));

	git_repository_free(repo2);

	git_reference_free(new_reference);
	git_reference_free(looked_up_ref);
	git_reference_free(resolved_ref);
}