#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int GIT_EEXISTS ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_ERROR_TAG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * git_object_owner (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int retrieve_tag_reference_oid (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ write_tag_annotation (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*) ; 

__attribute__((used)) static int git_tag_create__internal(
		git_oid *oid,
		git_repository *repo,
		const char *tag_name,
		const git_object *target,
		const git_signature *tagger,
		const char *message,
		int allow_ref_overwrite,
		int create_tag_annotation)
{
	git_reference *new_ref = NULL;
	git_buf ref_name = GIT_BUF_INIT;

	int error;

	assert(repo && tag_name && target);
	assert(!create_tag_annotation || (tagger && message));

	if (git_object_owner(target) != repo) {
		git_error_set(GIT_ERROR_INVALID, "the given target does not belong to this repository");
		return -1;
	}

	error = retrieve_tag_reference_oid(oid, &ref_name, repo, tag_name);
	if (error < 0 && error != GIT_ENOTFOUND)
		goto cleanup;

	/** Ensure the tag name doesn't conflict with an already existing
	 *	reference unless overwriting has explicitly been requested **/
	if (error == 0 && !allow_ref_overwrite) {
		git_buf_dispose(&ref_name);
		git_error_set(GIT_ERROR_TAG, "tag already exists");
		return GIT_EEXISTS;
	}

	if (create_tag_annotation) {
		if (write_tag_annotation(oid, repo, tag_name, target, tagger, message) < 0)
			return -1;
	} else
		git_oid_cpy(oid, git_object_id(target));

	error = git_reference_create(&new_ref, repo, ref_name.ptr, oid, allow_ref_overwrite, NULL);

cleanup:
	git_reference_free(new_ref);
	git_buf_dispose(&ref_name);
	return error;
}