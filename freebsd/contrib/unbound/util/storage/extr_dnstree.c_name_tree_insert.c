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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {struct name_tree_node* key; } ;
struct name_tree_node {size_t len; int labs; TYPE_1__ node; int /*<<< orphan*/ * parent; int /*<<< orphan*/  dclass; int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  rbtree_type ;

/* Variables and functions */
 int /*<<< orphan*/ * rbtree_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 

int name_tree_insert(rbtree_type* tree, struct name_tree_node* node, 
        uint8_t* name, size_t len, int labs, uint16_t dclass)
{
	node->node.key = node;
	node->name = name;
	node->len = len;
	node->labs = labs;
	node->dclass = dclass;
	node->parent = NULL;
	return rbtree_insert(tree, &node->node) != NULL;
}