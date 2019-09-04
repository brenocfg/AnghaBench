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
typedef  int /*<<< orphan*/  git_tree_entry ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int GIT_EEXISTS ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__ishex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_tree_entry_byindex (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_tree_entry_filemode (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_tree_entry_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_tree_entry_name (int /*<<< orphan*/  const*) ; 
 size_t git_tree_entrycount (int /*<<< orphan*/ *) ; 
 int git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int note_error_notfound () ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int find_subtree_in_current_level(
	git_tree **out,
	git_repository *repo,
	git_tree *parent,
	const char *annotated_object_sha,
	int fanout)
{
	size_t i;
	const git_tree_entry *entry;

	*out = NULL;

	if (parent == NULL)
		return note_error_notfound();

	for (i = 0; i < git_tree_entrycount(parent); i++) {
		entry = git_tree_entry_byindex(parent, i);

		if (!git__ishex(git_tree_entry_name(entry)))
			continue;

		if (S_ISDIR(git_tree_entry_filemode(entry))
			&& strlen(git_tree_entry_name(entry)) == 2
			&& !strncmp(git_tree_entry_name(entry), annotated_object_sha + fanout, 2))
			return git_tree_lookup(out, repo, git_tree_entry_id(entry));

		/* Not a DIR, so do we have an already existing blob? */
		if (!strcmp(git_tree_entry_name(entry), annotated_object_sha + fanout))
			return GIT_EEXISTS;
	}

	return note_error_notfound();
}