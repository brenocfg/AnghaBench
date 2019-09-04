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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int git_note_commit_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*,int) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int retrieve_note_commit (int /*<<< orphan*/ **,char**,int /*<<< orphan*/ *,char const*) ; 

int git_note_create(
	git_oid *out,
	git_repository *repo,
	const char *notes_ref_in,
	const git_signature *author,
	const git_signature *committer,
	const git_oid *oid,
	const char *note,
	int allow_note_overwrite)
{
	int error;
	char *notes_ref = NULL;
	git_commit *existing_notes_commit = NULL;
	git_reference *ref = NULL;
	git_oid notes_blob_oid, notes_commit_oid;

	error = retrieve_note_commit(&existing_notes_commit, &notes_ref,
			repo, notes_ref_in);

	if (error < 0 && error != GIT_ENOTFOUND)
		goto cleanup;

	error = git_note_commit_create(&notes_commit_oid,
			&notes_blob_oid,
			repo, existing_notes_commit, author,
			committer, oid, note,
			allow_note_overwrite);
	if (error < 0)
		goto cleanup;

	error = git_reference_create(&ref, repo, notes_ref,
				&notes_commit_oid, 1, NULL);

	if (out != NULL)
		git_oid_cpy(out, &notes_blob_oid);

cleanup:
	git__free(notes_ref);
	git_commit_free(existing_notes_commit);
	git_reference_free(ref);
	return error;
}