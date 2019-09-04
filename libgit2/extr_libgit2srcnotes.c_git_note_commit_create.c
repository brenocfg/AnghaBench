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
typedef  int /*<<< orphan*/  target ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OID_HEXSZ ; 
 int git_commit_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_tostr (char*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int note_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int) ; 

int git_note_commit_create(
	git_oid *notes_commit_out,
	git_oid *notes_blob_out,
	git_repository *repo,
	git_commit *parent,
	const git_signature *author,
	const git_signature *committer,
	const git_oid *oid,
	const char *note,
	int allow_note_overwrite)
{
	int error;
	git_tree *tree = NULL;
	char target[GIT_OID_HEXSZ + 1];

	git_oid_tostr(target, sizeof(target), oid);

	if (parent != NULL && (error = git_commit_tree(&tree, parent)) < 0)
		goto cleanup;

	error = note_write(notes_commit_out, notes_blob_out, repo, author,
			committer, NULL, note, tree, target, &parent, allow_note_overwrite);

	if (error < 0)
		goto cleanup;

cleanup:
	git_tree_free(tree);
	return error;
}