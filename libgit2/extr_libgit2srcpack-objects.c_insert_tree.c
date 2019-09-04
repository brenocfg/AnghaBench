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
struct walk_object {int seen; scalar_t__ uninteresting; int /*<<< orphan*/  const id; } ;
typedef  int /*<<< orphan*/  git_tree_entry ;
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_5__ {int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ git_packbuilder ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
#define  GIT_OBJECT_BLOB 129 
#define  GIT_OBJECT_TREE 128 
 int git_packbuilder_insert (TYPE_1__*,int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/ * git_tree_entry_byindex (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * git_tree_entry_id (int /*<<< orphan*/  const*) ; 
 char* git_tree_entry_name (int /*<<< orphan*/  const*) ; 
 int git_tree_entry_type (int /*<<< orphan*/  const*) ; 
 size_t git_tree_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* git_tree_id (int /*<<< orphan*/ *) ; 
 int git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int retrieve_object (struct walk_object**,TYPE_1__*,int /*<<< orphan*/  const*) ; 

int insert_tree(git_packbuilder *pb, git_tree *tree)
{
	size_t i;
	int error;
	git_tree *subtree;
	struct walk_object *obj;
	const char *name;

	if ((error = retrieve_object(&obj, pb, git_tree_id(tree))) < 0)
		return error;

	if (obj->seen || obj->uninteresting)
		return 0;

	obj->seen = 1;

	if ((error = git_packbuilder_insert(pb, &obj->id, NULL)))
		return error;

	for (i = 0; i < git_tree_entrycount(tree); i++) {
		const git_tree_entry *entry = git_tree_entry_byindex(tree, i);
		const git_oid *entry_id = git_tree_entry_id(entry);
		switch (git_tree_entry_type(entry)) {
		case GIT_OBJECT_TREE:
			if ((error = git_tree_lookup(&subtree, pb->repo, entry_id)) < 0)
				return error;

			error = insert_tree(pb, subtree);
			git_tree_free(subtree);

			if (error < 0)
				return error;

			break;
		case GIT_OBJECT_BLOB:
			if ((error = retrieve_object(&obj, pb, entry_id)) < 0)
				return error;
			if (obj->uninteresting)
				continue;
			name = git_tree_entry_name(entry);
			if ((error = git_packbuilder_insert(pb, entry_id, name)) < 0)
				return error;
			break;
		default:
			/* it's a submodule or something unknown, we don't want it */
			;
		}
	}


	return error;
}