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
struct name_tree_node {size_t len; int labs; int /*<<< orphan*/  dclass; int /*<<< orphan*/ * name; TYPE_1__ node; } ;
typedef  int /*<<< orphan*/  rbtree_type ;

/* Variables and functions */
 scalar_t__ rbtree_search (int /*<<< orphan*/ *,struct name_tree_node*) ; 

struct name_tree_node* name_tree_find(rbtree_type* tree, uint8_t* name, 
        size_t len, int labs, uint16_t dclass)
{
	struct name_tree_node key;
	key.node.key = &key;
	key.name = name;
	key.len = len;
	key.labs = labs;
	key.dclass = dclass;
	return (struct name_tree_node*)rbtree_search(tree, &key);
}