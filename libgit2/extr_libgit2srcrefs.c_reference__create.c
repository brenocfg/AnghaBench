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
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_refname_t ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_refdb ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GIT_ERROR_REFERENCE ; 
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_object__is_valid (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int git_refdb_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/ * git_reference__alloc (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_reference__alloc_symbolic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_reference__enable_symbolic_ref_target_validation ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_repository_refdb__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int reference_normalize_for_repo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static int reference__create(
	git_reference **ref_out,
	git_repository *repo,
	const char *name,
	const git_oid *oid,
	const char *symbolic,
	int force,
	const git_signature *signature,
	const char *log_message,
	const git_oid *old_id,
	const char *old_target)
{
	git_refname_t normalized;
	git_refdb *refdb;
	git_reference *ref = NULL;
	int error = 0;

	assert(repo && name);
	assert(symbolic || signature);

	if (ref_out)
		*ref_out = NULL;

	error = reference_normalize_for_repo(normalized, repo, name, true);
	if (error < 0)
		return error;

	error = git_repository_refdb__weakptr(&refdb, repo);
	if (error < 0)
		return error;

	if (oid != NULL) {
		assert(symbolic == NULL);

		if (!git_object__is_valid(repo, oid, GIT_OBJECT_ANY)) {
			git_error_set(GIT_ERROR_REFERENCE,
				"target OID for the reference doesn't exist on the repository");
			return -1;
		}

		ref = git_reference__alloc(normalized, oid, NULL);
	} else {
		git_refname_t normalized_target;

		error = reference_normalize_for_repo(normalized_target, repo,
			symbolic, git_reference__enable_symbolic_ref_target_validation);

		if (error < 0)
			return error;

		ref = git_reference__alloc_symbolic(normalized, normalized_target);
	}

	GIT_ERROR_CHECK_ALLOC(ref);

	if ((error = git_refdb_write(refdb, ref, force, signature, log_message, old_id, old_target)) < 0) {
		git_reference_free(ref);
		return error;
	}

	if (ref_out == NULL)
		git_reference_free(ref);
	else
		*ref_out = ref;

	return 0;
}