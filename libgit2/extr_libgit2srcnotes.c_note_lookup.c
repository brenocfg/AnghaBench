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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_note ;
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int find_blob (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int find_subtree_r (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int*) ; 
 int /*<<< orphan*/  git_blob_free (int /*<<< orphan*/ *) ; 
 int git_blob_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int note_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int note_lookup(
	git_note **out,
	git_repository *repo,
	git_commit *commit,
	git_tree *tree,
	const char *target)
{
	int error, fanout = 0;
	git_oid oid;
	git_blob *blob = NULL;
	git_note *note = NULL;
	git_tree *subtree = NULL;

	if ((error = find_subtree_r(&subtree, tree, repo, target, &fanout)) < 0)
		goto cleanup;

	if ((error = find_blob(&oid, subtree, target + fanout)) < 0)
		goto cleanup;

	if ((error = git_blob_lookup(&blob, repo, &oid)) < 0)
		goto cleanup;

	if ((error = note_new(&note, &oid, commit, blob)) < 0)
		goto cleanup;

	*out = note;

cleanup:
	git_tree_free(subtree);
	git_blob_free(blob);
	return error;
}