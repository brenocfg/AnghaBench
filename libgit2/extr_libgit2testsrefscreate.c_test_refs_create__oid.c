#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_reference ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int GIT_REFERENCE_DIRECT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_master_tip ; 
 int /*<<< orphan*/ * g_repo ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_create (TYPE_1__**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_reference_lookup (TYPE_1__**,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_reference_target (TYPE_1__*) ; 
 int git_reference_type (TYPE_1__*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,char*) ; 
 scalar_t__ reference_is_packed (TYPE_1__*) ; 

void test_refs_create__oid(void)
{
	/* create a new OID reference */
	git_reference *new_reference, *looked_up_ref;
	git_repository *repo2;
	git_oid id;

	const char *new_head = "refs/heads/new-head";

	git_oid_fromstr(&id, current_master_tip);

	/* Create and write the new object id reference */
	cl_git_pass(git_reference_create(&new_reference, g_repo, new_head, &id, 0, NULL));

	/* Ensure the reference can be looked-up... */
	cl_git_pass(git_reference_lookup(&looked_up_ref, g_repo, new_head));
	cl_assert(git_reference_type(looked_up_ref) & GIT_REFERENCE_DIRECT);
	cl_assert(reference_is_packed(looked_up_ref) == 0);
	cl_assert_equal_s(looked_up_ref->name, new_head);

	/* ...and that it points to the current master tip */
	cl_assert_equal_oid(&id, git_reference_target(looked_up_ref));
	git_reference_free(looked_up_ref);

	/* Similar test with a fresh new repository */
	cl_git_pass(git_repository_open(&repo2, "testrepo"));

	cl_git_pass(git_reference_lookup(&looked_up_ref, repo2, new_head));
	cl_assert_equal_oid(&id, git_reference_target(looked_up_ref));

	git_repository_free(repo2);

	git_reference_free(new_reference);
	git_reference_free(looked_up_ref);
}