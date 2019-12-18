#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  map; } ;
typedef  TYPE_1__ git_treebuilder ;
typedef  int /*<<< orphan*/  git_tree_entry ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * git_strmap_get (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static git_tree_entry *treebuilder_get(git_treebuilder *bld, const char *filename)
{
	assert(bld && filename);
	return git_strmap_get(bld->map, filename);
}