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
struct tree {int dummy; } ;
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct object {scalar_t__ type; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 scalar_t__ OBJ_COMMIT ; 
 scalar_t__ OBJ_TREE ; 
 struct object* deref_tag (struct repository*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 struct commit* make_virtual_commit (struct repository*,struct tree*,char const*) ; 
 scalar_t__ parse_commit (struct commit*) ; 
 int /*<<< orphan*/  parse_object (struct repository*,struct object_id const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static struct commit *get_ref(struct repository *repo,
			      const struct object_id *oid,
			      const char *name)
{
	struct object *object;

	object = deref_tag(repo, parse_object(repo, oid),
			   name, strlen(name));
	if (!object)
		return NULL;
	if (object->type == OBJ_TREE)
		return make_virtual_commit(repo, (struct tree*)object, name);
	if (object->type != OBJ_COMMIT)
		return NULL;
	if (parse_commit((struct commit *)object))
		return NULL;
	return (struct commit *)object;
}