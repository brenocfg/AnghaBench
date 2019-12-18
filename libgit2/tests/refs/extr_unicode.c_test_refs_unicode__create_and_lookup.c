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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 char const* REFNAME_DECOMPOSED ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_reference_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/ * repo ; 

void test_refs_unicode__create_and_lookup(void)
{
	git_reference *ref0, *ref1, *ref2;
	git_repository *repo2;

	const char *REFNAME = "refs/heads/" "\303\205" "ngstr" "\303\266" "m";
	const char *master = "refs/heads/master";

	/* Create the reference */
	cl_git_pass(git_reference_lookup(&ref0, repo, master));
	cl_git_pass(git_reference_create(
		&ref1, repo, REFNAME, git_reference_target(ref0), 0, NULL));
	cl_assert_equal_s(REFNAME, git_reference_name(ref1));
	git_reference_free(ref0);

	/* Lookup the reference in a different instance of the repository */
	cl_git_pass(git_repository_open(&repo2, "testrepo.git"));

	cl_git_pass(git_reference_lookup(&ref2, repo2, REFNAME));
	cl_assert_equal_oid(git_reference_target(ref1), git_reference_target(ref2));
	cl_assert_equal_s(REFNAME, git_reference_name(ref2));
	git_reference_free(ref2);

#if GIT_USE_ICONV
	/* Lookup reference by decomposed unicode name */

#define REFNAME_DECOMPOSED "refs/heads/" "A" "\314\212" "ngstro" "\314\210" "m"

	cl_git_pass(git_reference_lookup(&ref2, repo2, REFNAME_DECOMPOSED));
	cl_assert_equal_oid(git_reference_target(ref1), git_reference_target(ref2));
	cl_assert_equal_s(REFNAME, git_reference_name(ref2));
	git_reference_free(ref2);
#endif

	/* Cleanup */

	git_reference_free(ref1);
	git_repository_free(repo2);
}