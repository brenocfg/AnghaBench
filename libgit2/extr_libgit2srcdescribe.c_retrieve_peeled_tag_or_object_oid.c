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
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_reference_lookup_resolved (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int) ; 
 int git_reference_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int retrieve_peeled_tag_or_object_oid(
	git_oid *peeled_out,
	git_oid *ref_target_out,
	git_repository *repo,
	const char *refname)
{
	git_reference *ref;
	git_object *peeled = NULL;
	int error;

	if ((error = git_reference_lookup_resolved(&ref, repo, refname, -1)) < 0)
		return error;

	if ((error = git_reference_peel(&peeled, ref, GIT_OBJECT_ANY)) < 0)
		goto cleanup;

	git_oid_cpy(ref_target_out, git_reference_target(ref));
	git_oid_cpy(peeled_out, git_object_id(peeled));

	if (git_oid_cmp(ref_target_out, peeled_out) != 0)
		error = 1; /* The reference was pointing to a annotated tag */
	else
		error = 0; /* Any other object */

cleanup:
	git_reference_free(ref);
	git_object_free(peeled);
	return error;
}