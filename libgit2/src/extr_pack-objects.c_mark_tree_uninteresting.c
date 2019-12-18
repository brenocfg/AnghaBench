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
struct walk_object {int uninteresting; } ;
typedef  int /*<<< orphan*/  git_tree_entry ;
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_5__ {int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ git_packbuilder ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
#define  GIT_OBJECT_BLOB 129 
#define  GIT_OBJECT_TREE 128 
 int /*<<< orphan*/ * git_tree_entry_byindex (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * git_tree_entry_id (int /*<<< orphan*/  const*) ; 
 int git_tree_entry_type (int /*<<< orphan*/  const*) ; 
 size_t git_tree_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int mark_blob_uninteresting (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int retrieve_object (struct walk_object**,TYPE_1__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int mark_tree_uninteresting(git_packbuilder *pb, const git_oid *id)
{
	struct walk_object *obj;
	git_tree *tree;
	int error;
	size_t i;

	if ((error = retrieve_object(&obj, pb, id)) < 0)
		return error;

	if (obj->uninteresting)
		return 0;

	obj->uninteresting = 1;

	if ((error = git_tree_lookup(&tree, pb->repo, id)) < 0)
		return error;

	for (i = 0; i < git_tree_entrycount(tree); i++) {
		const git_tree_entry *entry = git_tree_entry_byindex(tree, i);
		const git_oid *entry_id = git_tree_entry_id(entry);
		switch (git_tree_entry_type(entry)) {
		case GIT_OBJECT_TREE:
			if ((error = mark_tree_uninteresting(pb, entry_id)) < 0)
				goto cleanup;
			break;
		case GIT_OBJECT_BLOB:
			if ((error = mark_blob_uninteresting(pb, entry_id)) < 0)
				goto cleanup;
			break;
		default:
			/* it's a submodule or something unknown, we don't want it */
			;
		}
	}

cleanup:
	git_tree_free(tree);
	return error;
}