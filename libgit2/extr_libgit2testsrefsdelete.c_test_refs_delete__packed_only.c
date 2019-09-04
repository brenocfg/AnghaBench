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
typedef  int /*<<< orphan*/  git_refdb ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_master_tip ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_refdb_compress (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_refdb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_repository_refdb (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int reference_is_packed (int /*<<< orphan*/ *) ; 

void test_refs_delete__packed_only(void)
{
	/* can delete a just packed reference */
	git_reference *ref;
	git_refdb *refdb;
	git_oid id;
	const char *new_ref = "refs/heads/new_ref";

	git_oid_fromstr(&id, current_master_tip);

	/* Create and write the new object id reference */
	cl_git_pass(git_reference_create(&ref, g_repo, new_ref, &id, 0, NULL));
	git_reference_free(ref);

	/* Lookup the reference */
	cl_git_pass(git_reference_lookup(&ref, g_repo, new_ref));

	/* Ensure it's a loose reference */
	cl_assert(reference_is_packed(ref) == 0);

	/* Pack all existing references */
	cl_git_pass(git_repository_refdb(&refdb, g_repo));
	cl_git_pass(git_refdb_compress(refdb));

	/* Reload the reference from disk */
	git_reference_free(ref);
	cl_git_pass(git_reference_lookup(&ref, g_repo, new_ref));

	/* Ensure it's a packed reference */
	cl_assert(reference_is_packed(ref) == 1);

	/* This should pass */
	cl_git_pass(git_reference_delete(ref));
	git_reference_free(ref);
	git_refdb_free(refdb);
}