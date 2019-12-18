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
typedef  int /*<<< orphan*/  git_odb ;
typedef  int /*<<< orphan*/  git_commit_parent_callback ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;
typedef  int /*<<< orphan*/  git_array_oid_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ARRAY_INIT ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  git_array_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_commit__create_buffer_internal (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 scalar_t__ git_odb__freshen (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ git_odb_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_reference__update_for_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_reference_lookup_resolved (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/ * git_reference_target (int /*<<< orphan*/ *) ; 
 scalar_t__ git_repository_odb__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int validate_tree_and_parents (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int git_commit__create_internal(
	git_oid *id,
	git_repository *repo,
	const char *update_ref,
	const git_signature *author,
	const git_signature *committer,
	const char *message_encoding,
	const char *message,
	const git_oid *tree,
	git_commit_parent_callback parent_cb,
	void *parent_payload,
	bool validate)
{
	int error;
	git_odb *odb;
	git_reference *ref = NULL;
	git_buf buf = GIT_BUF_INIT;
	const git_oid *current_id = NULL;
	git_array_oid_t parents = GIT_ARRAY_INIT;

	if (update_ref) {
		error = git_reference_lookup_resolved(&ref, repo, update_ref, 10);
		if (error < 0 && error != GIT_ENOTFOUND)
			return error;
	}
	git_error_clear();

	if (ref)
		current_id = git_reference_target(ref);

	if ((error = validate_tree_and_parents(&parents, repo, tree, parent_cb, parent_payload, current_id, validate)) < 0)
		goto cleanup;

	error = git_commit__create_buffer_internal(&buf, author, committer,
		message_encoding, message, tree,
		&parents);

	if (error < 0)
		goto cleanup;

	if (git_repository_odb__weakptr(&odb, repo) < 0)
		goto cleanup;

	if (git_odb__freshen(odb, tree) < 0)
		goto cleanup;

	if (git_odb_write(id, odb, buf.ptr, buf.size, GIT_OBJECT_COMMIT) < 0)
		goto cleanup;


	if (update_ref != NULL) {
		error = git_reference__update_for_commit(
			repo, ref, update_ref, id, "commit");
		goto cleanup;
	}

cleanup:
	git_array_clear(parents);
	git_reference_free(ref);
	git_buf_dispose(&buf);
	return error;
}