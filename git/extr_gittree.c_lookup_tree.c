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
struct object_id {int /*<<< orphan*/  hash; } ;
struct object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_TREE ; 
 int /*<<< orphan*/  alloc_tree_node (struct repository*) ; 
 struct tree* create_object (struct repository*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct object* lookup_object (struct repository*,int /*<<< orphan*/ ) ; 
 struct tree* object_as_type (struct repository*,struct object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct tree *lookup_tree(struct repository *r, const struct object_id *oid)
{
	struct object *obj = lookup_object(r, oid->hash);
	if (!obj)
		return create_object(r, oid->hash,
				     alloc_tree_node(r));
	return object_as_type(r, obj, OBJ_TREE, 0);
}