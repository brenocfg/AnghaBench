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
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct tree {TYPE_1__ object; } ;
struct repository {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_tree_entry (struct repository*,int /*<<< orphan*/ *,char const*,struct object_id*,unsigned short*) ; 

__attribute__((used)) static int tree_has_path(struct repository *r, struct tree *tree,
			 const char *path)
{
	struct object_id hashy;
	unsigned short mode_o;

	return !get_tree_entry(r,
			       &tree->object.oid, path,
			       &hashy, &mode_o);
}