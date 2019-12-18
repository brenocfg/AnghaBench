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
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char const*) ; 
 int /*<<< orphan*/  cl_git_fail (int) ; 
 int /*<<< orphan*/  cl_git_pass (int) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fmt (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 char const* git_reference_name (int /*<<< orphan*/ *) ; 
 int git_revparse_ext (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void test_object_and_ref_inrepo(
	const char *spec,
	const char *expected_oid,
	const char *expected_refname,
	git_repository *repo,
	bool assert_reference_retrieval)
{
	char objstr[64] = {0};
	git_object *obj = NULL;
	git_reference *ref = NULL;
	int error;

	error = git_revparse_ext(&obj, &ref, repo, spec);

	if (expected_oid != NULL) {
		cl_git_pass(error);
		git_oid_fmt(objstr, git_object_id(obj));
		cl_assert_equal_s(objstr, expected_oid);
	} else
		cl_git_fail(error);

	if (assert_reference_retrieval) {
		if (expected_refname == NULL)
			cl_assert(NULL == ref);
		else
			cl_assert_equal_s(expected_refname, git_reference_name(ref));
	}

	git_object_free(obj);
	git_reference_free(ref);
}