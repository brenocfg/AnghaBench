#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ uncompressed_base; scalar_t__ compressed_base; struct TYPE_5__* parent; struct TYPE_5__* left; struct TYPE_5__* right; } ;
typedef  TYPE_1__ index_tree_node ;
struct TYPE_6__ {scalar_t__ count; TYPE_1__* root; TYPE_1__* rightmost; TYPE_1__* leftmost; } ;
typedef  TYPE_2__ index_tree ;

/* Variables and functions */
 scalar_t__ UINT32_C (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bsr32 (scalar_t__) ; 
 scalar_t__ ctz32 (scalar_t__) ; 

__attribute__((used)) static void
index_tree_append(index_tree *tree, index_tree_node *node)
{
	node->parent = tree->rightmost;
	node->left = NULL;
	node->right = NULL;

	++tree->count;

	// Handle the special case of adding the first node.
	if (tree->root == NULL) {
		tree->root = node;
		tree->leftmost = node;
		tree->rightmost = node;
		return;
	}

	// The tree is always filled sequentially.
	assert(tree->rightmost->uncompressed_base <= node->uncompressed_base);
	assert(tree->rightmost->compressed_base < node->compressed_base);

	// Add the new node after the rightmost node. It's the correct
	// place due to the reason above.
	tree->rightmost->right = node;
	tree->rightmost = node;

	// Balance the AVL-tree if needed. We don't need to keep the balance
	// factors in nodes, because we always fill the tree sequentially,
	// and thus know the state of the tree just by looking at the node
	// count. From the node count we can calculate how many steps to go
	// up in the tree to find the rotation root.
	uint32_t up = tree->count ^ (UINT32_C(1) << bsr32(tree->count));
	if (up != 0) {
		// Locate the root node for the rotation.
		up = ctz32(tree->count) + 2;
		do {
			node = node->parent;
		} while (--up > 0);

		// Rotate left using node as the rotation root.
		index_tree_node *pivot = node->right;

		if (node->parent == NULL) {
			tree->root = pivot;
		} else {
			assert(node->parent->right == node);
			node->parent->right = pivot;
		}

		pivot->parent = node->parent;

		node->right = pivot->left;
		if (node->right != NULL)
			node->right->parent = node;

		pivot->left = node;
		node->parent = pivot;
	}

	return;
}