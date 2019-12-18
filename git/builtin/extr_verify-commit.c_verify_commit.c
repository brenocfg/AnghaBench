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
struct object {scalar_t__ type; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 scalar_t__ OBJ_COMMIT ; 
 int error (char*,char const*,...) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 struct object* parse_object (int /*<<< orphan*/ ,struct object_id*) ; 
 int run_gpg_verify (struct commit*,unsigned int) ; 
 int /*<<< orphan*/  the_repository ; 
 char* type_name (scalar_t__) ; 

__attribute__((used)) static int verify_commit(const char *name, unsigned flags)
{
	struct object_id oid;
	struct object *obj;

	if (get_oid(name, &oid))
		return error("commit '%s' not found.", name);

	obj = parse_object(the_repository, &oid);
	if (!obj)
		return error("%s: unable to read file.", name);
	if (obj->type != OBJ_COMMIT)
		return error("%s: cannot verify a non-commit object of type %s.",
				name, type_name(obj->type));

	return run_gpg_verify((struct commit *)obj, flags);
}