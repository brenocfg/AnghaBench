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
struct object {int type; } ;

/* Variables and functions */
 int OBJ_COMMIT ; 
 int OBJ_TAG ; 
 int OBJ_TREE ; 
 struct object* deref_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int oid_object_info (int /*<<< orphan*/ ,struct object_id const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_object (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int disambiguate_treeish_only(const struct object_id *oid, void *cb_data_unused)
{
	struct object *obj;
	int kind;

	kind = oid_object_info(the_repository, oid, NULL);
	if (kind == OBJ_TREE || kind == OBJ_COMMIT)
		return 1;
	if (kind != OBJ_TAG)
		return 0;

	/* We need to do this the hard way... */
	obj = deref_tag(the_repository, parse_object(the_repository, oid),
			NULL, 0);
	if (obj && (obj->type == OBJ_TREE || obj->type == OBJ_COMMIT))
		return 1;
	return 0;
}