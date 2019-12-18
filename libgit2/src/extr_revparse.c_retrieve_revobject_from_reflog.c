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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_reference_dwim (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_reference_target (int /*<<< orphan*/ *) ; 
 int retrieve_oid_from_reflog (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int retrieve_revobject_from_reflog(git_object **out, git_reference **base_ref, git_repository *repo, const char *identifier, size_t position)
{
	git_reference *ref;
	git_oid oid;
	int error = -1;

	if (*base_ref == NULL) {
		if ((error = git_reference_dwim(&ref, repo, identifier)) < 0)
			return error;
	} else {
		ref = *base_ref;
		*base_ref = NULL;
	}

	if (position == 0) {
		error = git_object_lookup(out, repo, git_reference_target(ref), GIT_OBJECT_ANY);
		goto cleanup;
	}

	if ((error = retrieve_oid_from_reflog(&oid, ref, position)) < 0)
		goto cleanup;

	error = git_object_lookup(out, repo, &oid, GIT_OBJECT_ANY);

cleanup:
	git_reference_free(ref);
	return error;
}