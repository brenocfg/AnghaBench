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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct iter_hints_stub {int /*<<< orphan*/  node; } ;
struct iter_hints {int /*<<< orphan*/  tree; } ;

/* Variables and functions */
 int dname_count_size_labels (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  hints_stub_free (struct iter_hints_stub*) ; 
 scalar_t__ name_tree_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  name_tree_init_parents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbtree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void 
hints_delete_stub(struct iter_hints* hints, uint16_t c, uint8_t* nm)
{
	struct iter_hints_stub *z;
	size_t len;
	int labs = dname_count_size_labels(nm, &len);
	if(!(z=(struct iter_hints_stub*)name_tree_find(&hints->tree,
		nm, len, labs, c)))
		return; /* nothing to do */
	(void)rbtree_delete(&hints->tree, &z->node);
	hints_stub_free(z);
	name_tree_init_parents(&hints->tree);
}