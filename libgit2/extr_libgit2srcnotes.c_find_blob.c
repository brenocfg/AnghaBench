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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_tree_entry_byindex (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_tree_entry_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_tree_entry_name (int /*<<< orphan*/  const*) ; 
 size_t git_tree_entrycount (int /*<<< orphan*/ *) ; 
 int note_error_notfound () ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int find_blob(git_oid *blob, git_tree *tree, const char *target)
{
	size_t i;
	const git_tree_entry *entry;

	for (i=0; i<git_tree_entrycount(tree); i++) {
		entry = git_tree_entry_byindex(tree, i);

		if (!strcmp(git_tree_entry_name(entry), target)) {
			/* found matching note object - return */

			git_oid_cpy(blob, git_tree_entry_id(entry));
			return 0;
		}
	}

	return note_error_notfound();
}