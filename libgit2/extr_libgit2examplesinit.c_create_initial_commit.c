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
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  fatal (char*,char*) ; 
 scalar_t__ git_commit_create_v (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_index_write_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ git_signature_default (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void create_initial_commit(git_repository *repo)
{
	git_signature *sig;
	git_index *index;
	git_oid tree_id, commit_id;
	git_tree *tree;

	/** First use the config to initialize a commit signature for the user. */

	if (git_signature_default(&sig, repo) < 0)
		fatal("Unable to create a commit signature.",
		      "Perhaps 'user.name' and 'user.email' are not set");

	/* Now let's create an empty tree for this commit */

	if (git_repository_index(&index, repo) < 0)
		fatal("Could not open repository index", NULL);

	/**
	 * Outside of this example, you could call git_index_add_bypath()
	 * here to put actual files into the index.  For our purposes, we'll
	 * leave it empty for now.
	 */

	if (git_index_write_tree(&tree_id, index) < 0)
		fatal("Unable to write initial tree from index", NULL);

	git_index_free(index);

	if (git_tree_lookup(&tree, repo, &tree_id) < 0)
		fatal("Could not look up initial tree", NULL);

	/**
	 * Ready to create the initial commit.
	 *
	 * Normally creating a commit would involve looking up the current
	 * HEAD commit and making that be the parent of the initial commit,
	 * but here this is the first commit so there will be no parent.
	 */

	if (git_commit_create_v(
			&commit_id, repo, "HEAD", sig, sig,
			NULL, "Initial commit", tree, 0) < 0)
		fatal("Could not create the initial commit", NULL);

	/** Clean up so we don't leak memory. */

	git_tree_free(tree);
	git_signature_free(sig);
}