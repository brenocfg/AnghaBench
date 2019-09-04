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
struct object {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ OBJ_TREE ; 
 int /*<<< orphan*/  free_tree_buffer (struct tree*) ; 
 int fsck_walk (struct object*,struct object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsck_walk_options ; 

__attribute__((used)) static int traverse_one_object(struct object *obj)
{
	int result = fsck_walk(obj, obj, &fsck_walk_options);

	if (obj->type == OBJ_TREE) {
		struct tree *tree = (struct tree *)obj;
		free_tree_buffer(tree);
	}
	return result;
}