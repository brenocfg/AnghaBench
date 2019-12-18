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
struct object_id {int dummy; } ;
struct object {scalar_t__ type; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  object_names; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_REACHABLE ; 
 int /*<<< orphan*/  ERROR_REFS ; 
 scalar_t__ OBJ_COMMIT ; 
 int /*<<< orphan*/  USED ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_decoration (int /*<<< orphan*/ ,struct object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_refs ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  errors_found ; 
 TYPE_1__ fsck_walk_options ; 
 scalar_t__ is_branch (char const*) ; 
 scalar_t__ is_promisor_object (struct object_id const*) ; 
 int /*<<< orphan*/  mark_object_reachable (struct object*) ; 
 scalar_t__ name_objects ; 
 char* oid_to_hex (struct object_id const*) ; 
 struct object* parse_object (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static int fsck_handle_ref(const char *refname, const struct object_id *oid,
			   int flag, void *cb_data)
{
	struct object *obj;

	obj = parse_object(the_repository, oid);
	if (!obj) {
		if (is_promisor_object(oid)) {
			/*
			 * Increment default_refs anyway, because this is a
			 * valid ref.
			 */
			 default_refs++;
			 return 0;
		}
		error(_("%s: invalid sha1 pointer %s"),
		      refname, oid_to_hex(oid));
		errors_found |= ERROR_REACHABLE;
		/* We'll continue with the rest despite the error.. */
		return 0;
	}
	if (obj->type != OBJ_COMMIT && is_branch(refname)) {
		error(_("%s: not a commit"), refname);
		errors_found |= ERROR_REFS;
	}
	default_refs++;
	obj->flags |= USED;
	if (name_objects)
		add_decoration(fsck_walk_options.object_names,
			obj, xstrdup(refname));
	mark_object_reachable(obj);

	return 0;
}