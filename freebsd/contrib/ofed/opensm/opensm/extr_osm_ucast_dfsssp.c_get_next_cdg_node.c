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
struct TYPE_4__ {int visited; scalar_t__ status; struct TYPE_4__* parent; struct TYPE_4__* right; struct TYPE_4__* left; } ;
typedef  TYPE_1__ cdg_node_t ;

/* Variables and functions */
 scalar_t__ UNKNOWN ; 

__attribute__((used)) static cdg_node_t *get_next_cdg_node(cdg_node_t * root)
{
	cdg_node_t *current = root, *res = NULL;

	while (current) {
		current->visited = 1;
		if (current->status == UNKNOWN) {
			res = current;
			break;
		}
		if (current->left && !current->left->visited) {
			current = current->left;
		} else if (current->right && !current->right->visited) {
			current = current->right;
		} else {
			if (current->left)
				current->left->visited = 0;
			if (current->right)
				current->right->visited = 0;
			if (current->parent == NULL)
				break;
			else
				current = current->parent;
		}
	}

	/* Clean up */
	while (current) {
		current->visited = 0;
		if (current->left)
			current->left->visited = 0;
		if (current->right)
			current->right->visited = 0;
		current = current->parent;
	}

	return res;
}