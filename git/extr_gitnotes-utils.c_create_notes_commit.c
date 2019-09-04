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
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct notes_tree {int /*<<< orphan*/  ref; int /*<<< orphan*/  initialized; } ;
struct commit_list {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commit_list_insert (struct commit*,struct commit_list**) ; 
 scalar_t__ commit_tree (char const*,size_t,struct object_id*,struct commit_list*,struct object_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 struct commit* lookup_commit (struct repository*,struct object_id*) ; 
 scalar_t__ parse_commit (struct commit*) ; 
 int /*<<< orphan*/  read_ref (int /*<<< orphan*/ ,struct object_id*) ; 
 scalar_t__ write_notes_tree (struct notes_tree*,struct object_id*) ; 

void create_notes_commit(struct repository *r,
			 struct notes_tree *t,
			 struct commit_list *parents,
			 const char *msg, size_t msg_len,
			 struct object_id *result_oid)
{
	struct object_id tree_oid;

	assert(t->initialized);

	if (write_notes_tree(t, &tree_oid))
		die("Failed to write notes tree to database");

	if (!parents) {
		/* Deduce parent commit from t->ref */
		struct object_id parent_oid;
		if (!read_ref(t->ref, &parent_oid)) {
			struct commit *parent = lookup_commit(r, &parent_oid);
			if (parse_commit(parent))
				die("Failed to find/parse commit %s", t->ref);
			commit_list_insert(parent, &parents);
		}
		/* else: t->ref points to nothing, assume root/orphan commit */
	}

	if (commit_tree(msg, msg_len, &tree_oid, parents, result_oid, NULL,
			NULL))
		die("Failed to commit notes tree to database");
}