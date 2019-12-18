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
typedef  int /*<<< orphan*/  uint16_t ;
struct iter_hints_stub {int /*<<< orphan*/  node; } ;
struct iter_hints {int /*<<< orphan*/  tree; } ;
struct delegpt {int /*<<< orphan*/  namelabs; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  hints_insert (struct iter_hints*,int /*<<< orphan*/ ,struct delegpt*,int) ; 
 int /*<<< orphan*/  hints_stub_free (struct iter_hints_stub*) ; 
 scalar_t__ name_tree_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  name_tree_init_parents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbtree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int 
hints_add_stub(struct iter_hints* hints, uint16_t c, struct delegpt* dp,
	int noprime)
{
	struct iter_hints_stub *z;
	if((z=(struct iter_hints_stub*)name_tree_find(&hints->tree,
		dp->name, dp->namelen, dp->namelabs, c)) != NULL) {
		(void)rbtree_delete(&hints->tree, &z->node);
		hints_stub_free(z);
	}
	if(!hints_insert(hints, c, dp, noprime))
		return 0;
	name_tree_init_parents(&hints->tree);
	return 1;
}