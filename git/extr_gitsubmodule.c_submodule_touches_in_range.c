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
struct string_list {int nr; } ;
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct argv_array {int dummy; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char*) ; 
 int /*<<< orphan*/  collect_changed_submodules (struct repository*,struct string_list*,struct argv_array*) ; 
 int /*<<< orphan*/  free_submodules_oids (struct string_list*) ; 
 int /*<<< orphan*/  is_null_oid (struct object_id*) ; 
 char* oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  submodule_from_path (struct repository*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int submodule_touches_in_range(struct repository *r,
			       struct object_id *excl_oid,
			       struct object_id *incl_oid)
{
	struct string_list subs = STRING_LIST_INIT_DUP;
	struct argv_array args = ARGV_ARRAY_INIT;
	int ret;

	/* No need to check if there are no submodules configured */
	if (!submodule_from_path(r, NULL, NULL))
		return 0;

	argv_array_push(&args, "--"); /* args[0] program name */
	argv_array_push(&args, oid_to_hex(incl_oid));
	if (!is_null_oid(excl_oid)) {
		argv_array_push(&args, "--not");
		argv_array_push(&args, oid_to_hex(excl_oid));
	}

	collect_changed_submodules(r, &subs, &args);
	ret = subs.nr;

	argv_array_clear(&args);

	free_submodules_oids(&subs);
	return ret;
}