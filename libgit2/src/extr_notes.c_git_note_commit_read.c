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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_note ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OID_HEXSZ ; 
 int git_commit_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_tostr (char*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int note_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

int git_note_commit_read(
	git_note **out,
	git_repository *repo,
	git_commit *notes_commit,
	const git_oid *oid)
{
	int error;
	git_tree *tree = NULL;
	char target[GIT_OID_HEXSZ + 1];

	git_oid_tostr(target, sizeof(target), oid);

	if ((error = git_commit_tree(&tree, notes_commit)) < 0)
		goto cleanup;

	error = note_lookup(out, repo, notes_commit, tree, target);

cleanup:
	git_tree_free(tree);
	return error;
}