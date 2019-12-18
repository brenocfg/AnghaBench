#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t avl_offset; int /*<<< orphan*/ * avl_root; } ;
typedef  TYPE_1__ avl_tree_t ;
typedef  int /*<<< orphan*/  avl_node_t ;
typedef  int /*<<< orphan*/  avl_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int AVL_INDEX2CHILD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * AVL_INDEX2NODE (int /*<<< orphan*/ ) ; 
 void* AVL_NODE2DATA (int /*<<< orphan*/ *,size_t) ; 
 void* avl_walk (TYPE_1__*,void*,int) ; 

void *
avl_nearest(avl_tree_t *tree, avl_index_t where, int direction)
{
	int child = AVL_INDEX2CHILD(where);
	avl_node_t *node = AVL_INDEX2NODE(where);
	void *data;
	size_t off = tree->avl_offset;

	if (node == NULL) {
		ASSERT(tree->avl_root == NULL);
		return (NULL);
	}
	data = AVL_NODE2DATA(node, off);
	if (child != direction)
		return (data);

	return (avl_walk(tree, data, direction));
}