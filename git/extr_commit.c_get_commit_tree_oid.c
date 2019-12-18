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
struct TYPE_2__ {struct object_id oid; } ;
struct tree {TYPE_1__ object; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 struct tree* get_commit_tree (struct commit const*) ; 

struct object_id *get_commit_tree_oid(const struct commit *commit)
{
	struct tree *tree = get_commit_tree(commit);
	return tree ? &tree->object.oid : NULL;
}