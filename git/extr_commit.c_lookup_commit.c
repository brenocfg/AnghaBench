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
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct object {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_COMMIT ; 
 int /*<<< orphan*/  alloc_commit_node (struct repository*) ; 
 struct commit* create_object (struct repository*,struct object_id const*,int /*<<< orphan*/ ) ; 
 struct object* lookup_object (struct repository*,struct object_id const*) ; 
 struct commit* object_as_type (struct repository*,struct object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct commit *lookup_commit(struct repository *r, const struct object_id *oid)
{
	struct object *obj = lookup_object(r, oid);
	if (!obj)
		return create_object(r, oid, alloc_commit_node(r));
	return object_as_type(r, obj, OBJ_COMMIT, 0);
}