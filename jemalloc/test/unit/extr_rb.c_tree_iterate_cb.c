#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree_t ;
struct TYPE_12__ {int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ node_t ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_MAGIC ; 
 int /*<<< orphan*/  assert_ptr_eq (TYPE_1__*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  assert_u32_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* tree_nsearch (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* tree_psearch (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* tree_search (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static node_t *
tree_iterate_cb(tree_t *tree, node_t *node, void *data) {
	unsigned *i = (unsigned *)data;
	node_t *search_node;

	assert_u32_eq(node->magic, NODE_MAGIC, "Bad magic");

	/* Test rb_search(). */
	search_node = tree_search(tree, node);
	assert_ptr_eq(search_node, node,
	    "tree_search() returned unexpected node");

	/* Test rb_nsearch(). */
	search_node = tree_nsearch(tree, node);
	assert_ptr_eq(search_node, node,
	    "tree_nsearch() returned unexpected node");

	/* Test rb_psearch(). */
	search_node = tree_psearch(tree, node);
	assert_ptr_eq(search_node, node,
	    "tree_psearch() returned unexpected node");

	(*i)++;

	return NULL;
}