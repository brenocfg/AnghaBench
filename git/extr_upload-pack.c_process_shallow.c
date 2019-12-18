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
struct object_id {int dummy; } ;
struct object_array {int dummy; } ;
struct object {scalar_t__ type; int flags; } ;

/* Variables and functions */
 int CLIENT_SHALLOW ; 
 scalar_t__ OBJ_COMMIT ; 
 int /*<<< orphan*/  add_object_array (struct object*,int /*<<< orphan*/ *,struct object_array*) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 scalar_t__ get_oid_hex (char const*,struct object_id*) ; 
 char const* oid_to_hex (struct object_id*) ; 
 struct object* parse_object (int /*<<< orphan*/ ,struct object_id*) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int process_shallow(const char *line, struct object_array *shallows)
{
	const char *arg;
	if (skip_prefix(line, "shallow ", &arg)) {
		struct object_id oid;
		struct object *object;
		if (get_oid_hex(arg, &oid))
			die("invalid shallow line: %s", line);
		object = parse_object(the_repository, &oid);
		if (!object)
			return 1;
		if (object->type != OBJ_COMMIT)
			die("invalid shallow object %s", oid_to_hex(&oid));
		if (!(object->flags & CLIENT_SHALLOW)) {
			object->flags |= CLIENT_SHALLOW;
			add_object_array(object, NULL, shallows);
		}
		return 1;
	}

	return 0;
}