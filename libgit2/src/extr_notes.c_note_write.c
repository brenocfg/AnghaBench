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
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_NOTES_DEFAULT_MSG_ADD ; 
 int git_blob_create_from_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int git_commit_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_note_in_tree_eexists_cb ; 
 int /*<<< orphan*/  insert_note_in_tree_enotfound_cb ; 
 int manipulate_note_in_tree_r (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int note_write(
	git_oid *notes_commit_out,
	git_oid *notes_blob_out,
	git_repository *repo,
	const git_signature *author,
	const git_signature *committer,
	const char *notes_ref,
	const char *note,
	git_tree *commit_tree,
	const char *target,
	git_commit **parents,
	int allow_note_overwrite)
{
	int error;
	git_oid oid;
	git_tree *tree = NULL;

	/* TODO: should we apply filters? */
	/* create note object */
	if ((error = git_blob_create_from_buffer(&oid, repo, note, strlen(note))) < 0)
		goto cleanup;

	if ((error = manipulate_note_in_tree_r(
		&tree, repo, commit_tree, &oid, target, 0,
		allow_note_overwrite ? insert_note_in_tree_enotfound_cb : insert_note_in_tree_eexists_cb,
		insert_note_in_tree_enotfound_cb)) < 0)
		goto cleanup;

	if (notes_blob_out)
		git_oid_cpy(notes_blob_out, &oid);


	error = git_commit_create(&oid, repo, notes_ref, author, committer,
				  NULL, GIT_NOTES_DEFAULT_MSG_ADD,
				  tree, *parents == NULL ? 0 : 1, (const git_commit **) parents);

	if (notes_commit_out)
		git_oid_cpy(notes_commit_out, &oid);

cleanup:
	git_tree_free(tree);
	return error;
}