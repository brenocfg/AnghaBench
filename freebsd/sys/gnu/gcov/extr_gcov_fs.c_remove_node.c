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
struct gcov_node {struct gcov_node* parent; int /*<<< orphan*/  children; } ;

/* Variables and functions */
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_node (struct gcov_node*) ; 
 struct gcov_node root_node ; 

__attribute__((used)) static void
remove_node(struct gcov_node *node)
{
	struct gcov_node *parent;

	while ((node != &root_node) && LIST_EMPTY(&node->children)) {
		parent = node->parent;
		release_node(node);
		node = parent;
	}
}