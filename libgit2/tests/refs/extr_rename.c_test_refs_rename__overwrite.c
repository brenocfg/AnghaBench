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
 int GIT_REFERENCE_DIRECT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_refdb_compress (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_refdb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 int git_reference_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_refdb (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ref_master_name ; 
 int /*<<< orphan*/  ref_one_name ; 
 int /*<<< orphan*/  ref_one_name_new ; 
 int /*<<< orphan*/  ref_two_name ; 

void test_refs_rename__overwrite(void)
{
	/* can not overwrite name of existing reference */
	git_reference *ref, *ref_one, *ref_one_new, *ref_two;
	git_refdb *refdb;
	git_oid id;

	cl_git_pass(git_reference_lookup(&ref, g_repo, ref_master_name));
	cl_assert(git_reference_type(ref) & GIT_REFERENCE_DIRECT);

	git_oid_cpy(&id, git_reference_target(ref));

	/* Create loose references */
	cl_git_pass(git_reference_create(&ref_one, g_repo, ref_one_name, &id, 0, NULL));
	cl_git_pass(git_reference_create(&ref_two, g_repo, ref_two_name, &id, 0, NULL));

	/* Pack everything */
	cl_git_pass(git_repository_refdb(&refdb, g_repo));
	cl_git_pass(git_refdb_compress(refdb));

	/* Attempt to create illegal reference */
	cl_git_fail(git_reference_create(&ref_one_new, g_repo, ref_one_name_new, &id, 0, NULL));

	/* Illegal reference couldn't be created so this is supposed to fail */
	cl_git_fail(git_reference_lookup(&ref_one_new, g_repo, ref_one_name_new));

	git_reference_free(ref);
	git_reference_free(ref_one);
	git_reference_free(ref_one_new);
	git_reference_free(ref_two);
	git_refdb_free(refdb);
}