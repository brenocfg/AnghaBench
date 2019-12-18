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
struct rev_info {scalar_t__ exclude_promisor_objects; scalar_t__ ignore_missing; int /*<<< orphan*/  repo; } ;
struct object_id {int dummy; } ;
struct object {unsigned int flags; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 scalar_t__ OBJ_COMMIT ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 scalar_t__ is_promisor_object (struct object_id const*) ; 
 struct commit* lookup_commit (int /*<<< orphan*/ ,struct object_id const*) ; 
 scalar_t__ oid_object_info (int /*<<< orphan*/ ,struct object_id const*,int /*<<< orphan*/ *) ; 
 struct object* parse_object (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  repo_parse_commit (int /*<<< orphan*/ ,struct commit*) ; 

__attribute__((used)) static struct object *get_reference(struct rev_info *revs, const char *name,
				    const struct object_id *oid,
				    unsigned int flags)
{
	struct object *object;

	/*
	 * If the repository has commit graphs, repo_parse_commit() avoids
	 * reading the object buffer, so use it whenever possible.
	 */
	if (oid_object_info(revs->repo, oid, NULL) == OBJ_COMMIT) {
		struct commit *c = lookup_commit(revs->repo, oid);
		if (!repo_parse_commit(revs->repo, c))
			object = (struct object *) c;
		else
			object = NULL;
	} else {
		object = parse_object(revs->repo, oid);
	}

	if (!object) {
		if (revs->ignore_missing)
			return object;
		if (revs->exclude_promisor_objects && is_promisor_object(oid))
			return NULL;
		die("bad object %s", name);
	}
	object->flags |= flags;
	return object;
}