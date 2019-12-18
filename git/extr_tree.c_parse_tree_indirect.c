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
struct object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_TREE ; 
 struct object* parse_object (struct repository*,struct object_id const*) ; 
 scalar_t__ repo_peel_to_type (struct repository*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct object*,int /*<<< orphan*/ ) ; 
 struct repository* the_repository ; 

struct tree *parse_tree_indirect(const struct object_id *oid)
{
	struct repository *r = the_repository;
	struct object *obj = parse_object(r, oid);
	return (struct tree *)repo_peel_to_type(r, NULL, 0, obj, OBJ_TREE);
}