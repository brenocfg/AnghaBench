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
struct tree {int dummy; } ;
struct tag {struct object* tagged; } ;
struct object_id {int dummy; } ;
struct object {scalar_t__ type; struct object_id const oid; int /*<<< orphan*/  parsed; } ;
struct commit {int dummy; } ;
struct TYPE_2__ {struct object object; } ;

/* Variables and functions */
 scalar_t__ OBJ_COMMIT ; 
 scalar_t__ OBJ_TAG ; 
 scalar_t__ OBJ_TREE ; 
 TYPE_1__* get_commit_tree (struct commit*) ; 
 struct object* parse_object (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  the_repository ; 

struct tree *parse_tree_indirect(const struct object_id *oid)
{
	struct object *obj = parse_object(the_repository, oid);
	do {
		if (!obj)
			return NULL;
		if (obj->type == OBJ_TREE)
			return (struct tree *) obj;
		else if (obj->type == OBJ_COMMIT)
			obj = &(get_commit_tree(((struct commit *)obj))->object);
		else if (obj->type == OBJ_TAG)
			obj = ((struct tag *) obj)->tagged;
		else
			return NULL;
		if (!obj->parsed)
			parse_object(the_repository, &obj->oid);
	} while (1);
}