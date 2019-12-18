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
struct packet_writer {int dummy; } ;
struct object_array {int nr; TYPE_1__* objects; } ;
struct object {int flags; int /*<<< orphan*/  oid; scalar_t__ parsed; } ;
struct commit_list {struct commit_list* next; TYPE_2__* item; } ;
struct commit {struct commit_list* parents; } ;
struct TYPE_4__ {struct object object; } ;
struct TYPE_3__ {struct object* item; } ;

/* Variables and functions */
 int CLIENT_SHALLOW ; 
 int NOT_SHALLOW ; 
 int /*<<< orphan*/  add_object_array (struct object*,int /*<<< orphan*/ *,struct object_array*) ; 
 struct object_array extra_edge_obj ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_writer_write (struct packet_writer*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_commit_or_die (struct commit*) ; 
 int /*<<< orphan*/  register_shallow (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  unregister_shallow (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void send_unshallow(struct packet_writer *writer,
			   const struct object_array *shallows,
			   struct object_array *want_obj)
{
	int i;

	for (i = 0; i < shallows->nr; i++) {
		struct object *object = shallows->objects[i].item;
		if (object->flags & NOT_SHALLOW) {
			struct commit_list *parents;
			packet_writer_write(writer, "unshallow %s",
					    oid_to_hex(&object->oid));
			object->flags &= ~CLIENT_SHALLOW;
			/*
			 * We want to _register_ "object" as shallow, but we
			 * also need to traverse object's parents to deepen a
			 * shallow clone. Unregister it for now so we can
			 * parse and add the parents to the want list, then
			 * re-register it.
			 */
			unregister_shallow(&object->oid);
			object->parsed = 0;
			parse_commit_or_die((struct commit *)object);
			parents = ((struct commit *)object)->parents;
			while (parents) {
				add_object_array(&parents->item->object,
						 NULL, want_obj);
				parents = parents->next;
			}
			add_object_array(object, NULL, &extra_edge_obj);
		}
		/* make sure commit traversal conforms to client */
		register_shallow(the_repository, &object->oid);
	}
}