#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct commit_list {int dummy; } ;
struct commit_graft {scalar_t__ nr_parent; struct object_id* parent; } ;
struct TYPE_4__ {int parsed; int /*<<< orphan*/  oid; } ;
struct commit {int /*<<< orphan*/  date; TYPE_1__ object; struct commit_list* parents; } ;
struct TYPE_6__ {struct commit_list* next; } ;
struct TYPE_5__ {int hexsz; } ;

/* Variables and functions */
 TYPE_3__* commit_list_insert (struct commit*,struct commit_list**) ; 
 int error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_oid_hex (char const*,struct object_id*) ; 
 scalar_t__ grafts_replace_parents ; 
 int /*<<< orphan*/  load_commit_graph_info (struct repository*,struct commit*) ; 
 struct commit* lookup_commit (struct repository*,struct object_id*) ; 
 struct commit_graft* lookup_commit_graft (struct repository*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lookup_tree (struct repository*,struct object_id*) ; 
 scalar_t__ memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_commit_date (char const*,char const*) ; 
 int /*<<< orphan*/  set_commit_tree (struct commit*,int /*<<< orphan*/ ) ; 
 TYPE_2__* the_hash_algo ; 

int parse_commit_buffer(struct repository *r, struct commit *item, const void *buffer, unsigned long size, int check_graph)
{
	const char *tail = buffer;
	const char *bufptr = buffer;
	struct object_id parent;
	struct commit_list **pptr;
	struct commit_graft *graft;
	const int tree_entry_len = the_hash_algo->hexsz + 5;
	const int parent_entry_len = the_hash_algo->hexsz + 7;

	if (item->object.parsed)
		return 0;
	item->object.parsed = 1;
	tail += size;
	if (tail <= bufptr + tree_entry_len + 1 || memcmp(bufptr, "tree ", 5) ||
			bufptr[tree_entry_len] != '\n')
		return error("bogus commit object %s", oid_to_hex(&item->object.oid));
	if (get_oid_hex(bufptr + 5, &parent) < 0)
		return error("bad tree pointer in commit %s",
			     oid_to_hex(&item->object.oid));
	set_commit_tree(item, lookup_tree(r, &parent));
	bufptr += tree_entry_len + 1; /* "tree " + "hex sha1" + "\n" */
	pptr = &item->parents;

	graft = lookup_commit_graft(r, &item->object.oid);
	while (bufptr + parent_entry_len < tail && !memcmp(bufptr, "parent ", 7)) {
		struct commit *new_parent;

		if (tail <= bufptr + parent_entry_len + 1 ||
		    get_oid_hex(bufptr + 7, &parent) ||
		    bufptr[parent_entry_len] != '\n')
			return error("bad parents in commit %s", oid_to_hex(&item->object.oid));
		bufptr += parent_entry_len + 1;
		/*
		 * The clone is shallow if nr_parent < 0, and we must
		 * not traverse its real parents even when we unhide them.
		 */
		if (graft && (graft->nr_parent < 0 || grafts_replace_parents))
			continue;
		new_parent = lookup_commit(r, &parent);
		if (new_parent)
			pptr = &commit_list_insert(new_parent, pptr)->next;
	}
	if (graft) {
		int i;
		struct commit *new_parent;
		for (i = 0; i < graft->nr_parent; i++) {
			new_parent = lookup_commit(r,
						   &graft->parent[i]);
			if (!new_parent)
				continue;
			pptr = &commit_list_insert(new_parent, pptr)->next;
		}
	}
	item->date = parse_commit_date(bufptr, tail);

	if (check_graph)
		load_commit_graph_info(r, item);

	return 0;
}