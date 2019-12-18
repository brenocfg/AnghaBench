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
struct object {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_COMMIT ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 int /*<<< orphan*/  merge_remote_util (struct commit*) ; 
 struct object* parse_object (int /*<<< orphan*/ ,struct object_id*) ; 
 scalar_t__ peel_to_type (char const*,int /*<<< orphan*/ ,struct object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_merge_remote_desc (struct commit*,char const*,struct object*) ; 
 int /*<<< orphan*/  the_repository ; 

struct commit *get_merge_parent(const char *name)
{
	struct object *obj;
	struct commit *commit;
	struct object_id oid;
	if (get_oid(name, &oid))
		return NULL;
	obj = parse_object(the_repository, &oid);
	commit = (struct commit *)peel_to_type(name, 0, obj, OBJ_COMMIT);
	if (commit && !merge_remote_util(commit))
		set_merge_remote_desc(commit, name, obj);
	return commit;
}