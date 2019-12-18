#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ lzma_vli ;
struct TYPE_6__ {scalar_t__ uncompressed_base; struct TYPE_6__* right; struct TYPE_6__* left; } ;
typedef  TYPE_2__ index_tree_node ;
struct TYPE_7__ {TYPE_1__* leftmost; TYPE_2__* root; } ;
typedef  TYPE_3__ index_tree ;
struct TYPE_5__ {scalar_t__ uncompressed_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void *
index_tree_locate(const index_tree *tree, lzma_vli target)
{
	const index_tree_node *result = NULL;
	const index_tree_node *node = tree->root;

	assert(tree->leftmost == NULL
			|| tree->leftmost->uncompressed_base == 0);

	// Consecutive nodes may have the same uncompressed_base.
	// We must pick the rightmost one.
	while (node != NULL) {
		if (node->uncompressed_base > target) {
			node = node->left;
		} else {
			result = node;
			node = node->right;
		}
	}

	return (void *)(result);
}