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
struct tag {struct object* tagged; } ;
struct repository {int dummy; } ;
struct object {int type; int /*<<< orphan*/  oid; int /*<<< orphan*/  parsed; } ;
struct commit {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_2__ {struct object object; } ;

/* Variables and functions */
 int OBJ_ANY ; 
 scalar_t__ OBJ_COMMIT ; 
 scalar_t__ OBJ_TAG ; 
 int /*<<< orphan*/  error (char*,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_object (struct repository*,int /*<<< orphan*/ *) ; 
 TYPE_1__* repo_get_commit_tree (struct repository*,struct commit*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  type_name (int) ; 

struct object *repo_peel_to_type(struct repository *r, const char *name, int namelen,
				 struct object *o, enum object_type expected_type)
{
	if (name && !namelen)
		namelen = strlen(name);
	while (1) {
		if (!o || (!o->parsed && !parse_object(r, &o->oid)))
			return NULL;
		if (expected_type == OBJ_ANY || o->type == expected_type)
			return o;
		if (o->type == OBJ_TAG)
			o = ((struct tag*) o)->tagged;
		else if (o->type == OBJ_COMMIT)
			o = &(repo_get_commit_tree(r, ((struct commit *)o))->object);
		else {
			if (name)
				error("%.*s: expected %s type, but the object "
				      "dereferences to %s type",
				      namelen, name, type_name(expected_type),
				      type_name(o->type));
			return NULL;
		}
	}
}