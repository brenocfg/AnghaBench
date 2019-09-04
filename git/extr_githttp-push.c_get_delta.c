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
struct tree {int dummy; } ;
struct TYPE_3__ {int nr; struct object_array_entry* objects; } ;
struct rev_info {TYPE_1__ pending; } ;
struct remote_lock {int dummy; } ;
struct object_list {struct object_list* next; TYPE_2__* item; } ;
struct object_array_entry {char* name; struct object* item; } ;
struct object {int flags; scalar_t__ type; int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {int flags; } ;
struct commit {TYPE_2__ object; } ;
struct blob {int dummy; } ;

/* Variables and functions */
 int LOCAL ; 
 scalar_t__ OBJ_BLOB ; 
 scalar_t__ OBJ_TAG ; 
 scalar_t__ OBJ_TREE ; 
 int SEEN ; 
 int UNINTERESTING ; 
 struct object_list** add_one_object (struct object*,struct object_list**) ; 
 scalar_t__ add_send_request (TYPE_2__*,struct remote_lock*) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ,char const*) ; 
 struct tree* get_commit_tree (struct commit*) ; 
 struct commit* get_revision (struct rev_info*) ; 
 struct object_list* objects ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 struct object_list** process_blob (struct blob*,struct object_list**) ; 
 struct object_list** process_tree (struct tree*,struct object_list**) ; 

__attribute__((used)) static int get_delta(struct rev_info *revs, struct remote_lock *lock)
{
	int i;
	struct commit *commit;
	struct object_list **p = &objects;
	int count = 0;

	while ((commit = get_revision(revs)) != NULL) {
		p = process_tree(get_commit_tree(commit), p);
		commit->object.flags |= LOCAL;
		if (!(commit->object.flags & UNINTERESTING))
			count += add_send_request(&commit->object, lock);
	}

	for (i = 0; i < revs->pending.nr; i++) {
		struct object_array_entry *entry = revs->pending.objects + i;
		struct object *obj = entry->item;
		const char *name = entry->name;

		if (obj->flags & (UNINTERESTING | SEEN))
			continue;
		if (obj->type == OBJ_TAG) {
			obj->flags |= SEEN;
			p = add_one_object(obj, p);
			continue;
		}
		if (obj->type == OBJ_TREE) {
			p = process_tree((struct tree *)obj, p);
			continue;
		}
		if (obj->type == OBJ_BLOB) {
			p = process_blob((struct blob *)obj, p);
			continue;
		}
		die("unknown pending object %s (%s)", oid_to_hex(&obj->oid), name);
	}

	while (objects) {
		if (!(objects->item->flags & UNINTERESTING))
			count += add_send_request(objects->item, lock);
		objects = objects->next;
	}

	return count;
}