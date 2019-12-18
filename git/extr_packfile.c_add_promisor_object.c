#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct tree_desc {int dummy; } ;
struct tree {int /*<<< orphan*/  size; int /*<<< orphan*/  buffer; } ;
struct tag {int dummy; } ;
struct packed_git {int dummy; } ;
struct oidset {int dummy; } ;
struct object_id {int dummy; } ;
struct object {scalar_t__ type; } ;
struct name_entry {struct object_id const oid; } ;
struct commit_list {TYPE_2__* item; struct commit_list* next; } ;
struct commit {struct commit_list* parents; } ;
struct TYPE_3__ {struct object_id const oid; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 scalar_t__ OBJ_COMMIT ; 
 scalar_t__ OBJ_TAG ; 
 scalar_t__ OBJ_TREE ; 
 struct object_id const* get_commit_tree_oid (struct commit*) ; 
 struct object_id const* get_tagged_oid (struct tag*) ; 
 scalar_t__ init_tree_desc_gently (struct tree_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oidset_insert (struct oidset*,struct object_id const*) ; 
 struct object* parse_object (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  the_repository ; 
 scalar_t__ tree_entry_gently (struct tree_desc*,struct name_entry*) ; 

__attribute__((used)) static int add_promisor_object(const struct object_id *oid,
			       struct packed_git *pack,
			       uint32_t pos,
			       void *set_)
{
	struct oidset *set = set_;
	struct object *obj = parse_object(the_repository, oid);
	if (!obj)
		return 1;

	oidset_insert(set, oid);

	/*
	 * If this is a tree, commit, or tag, the objects it refers
	 * to are also promisor objects. (Blobs refer to no objects->)
	 */
	if (obj->type == OBJ_TREE) {
		struct tree *tree = (struct tree *)obj;
		struct tree_desc desc;
		struct name_entry entry;
		if (init_tree_desc_gently(&desc, tree->buffer, tree->size))
			/*
			 * Error messages are given when packs are
			 * verified, so do not print any here.
			 */
			return 0;
		while (tree_entry_gently(&desc, &entry))
			oidset_insert(set, &entry.oid);
	} else if (obj->type == OBJ_COMMIT) {
		struct commit *commit = (struct commit *) obj;
		struct commit_list *parents = commit->parents;

		oidset_insert(set, get_commit_tree_oid(commit));
		for (; parents; parents = parents->next)
			oidset_insert(set, &parents->item->object.oid);
	} else if (obj->type == OBJ_TAG) {
		struct tag *tag = (struct tag *) obj;
		oidset_insert(set, get_tagged_oid(tag));
	}
	return 0;
}