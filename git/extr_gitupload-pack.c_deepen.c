#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct packet_writer {int dummy; } ;
struct object_array {int nr; TYPE_1__* objects; } ;
struct object {int /*<<< orphan*/  flags; } ;
struct commit_list {int dummy; } ;
struct TYPE_2__ {struct object* item; } ;

/* Variables and functions */
 int INFINITE_DEPTH ; 
 int /*<<< orphan*/  NOT_SHALLOW ; 
 struct object_array OBJECT_ARRAY_INIT ; 
 int /*<<< orphan*/  SHALLOW ; 
 int /*<<< orphan*/  check_ref ; 
 int /*<<< orphan*/  for_each_namespaced_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 int /*<<< orphan*/  get_reachable_list (struct object_array*,struct object_array*) ; 
 struct commit_list* get_shallow_commits (struct object_array*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  head_ref_namespaced (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_repository_shallow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  object_array_clear (struct object_array*) ; 
 int /*<<< orphan*/  send_shallow (struct packet_writer*,struct commit_list*) ; 
 int /*<<< orphan*/  send_unshallow (struct packet_writer*,struct object_array*,struct object_array*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void deepen(struct packet_writer *writer, int depth, int deepen_relative,
		   struct object_array *shallows, struct object_array *want_obj)
{
	if (depth == INFINITE_DEPTH && !is_repository_shallow(the_repository)) {
		int i;

		for (i = 0; i < shallows->nr; i++) {
			struct object *object = shallows->objects[i].item;
			object->flags |= NOT_SHALLOW;
		}
	} else if (deepen_relative) {
		struct object_array reachable_shallows = OBJECT_ARRAY_INIT;
		struct commit_list *result;

		/*
		 * Checking for reachable shallows requires that our refs be
		 * marked with OUR_REF.
		 */
		head_ref_namespaced(check_ref, NULL);
		for_each_namespaced_ref(check_ref, NULL);

		get_reachable_list(shallows, &reachable_shallows);
		result = get_shallow_commits(&reachable_shallows,
					     depth + 1,
					     SHALLOW, NOT_SHALLOW);
		send_shallow(writer, result);
		free_commit_list(result);
		object_array_clear(&reachable_shallows);
	} else {
		struct commit_list *result;

		result = get_shallow_commits(want_obj, depth,
					     SHALLOW, NOT_SHALLOW);
		send_shallow(writer, result);
		free_commit_list(result);
	}

	send_unshallow(writer, shallows, want_obj);
}