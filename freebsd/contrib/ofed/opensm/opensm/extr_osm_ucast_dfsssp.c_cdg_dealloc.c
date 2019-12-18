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
struct TYPE_4__ {struct TYPE_4__* right; struct TYPE_4__* parent; struct TYPE_4__* left; } ;
typedef  TYPE_1__ cdg_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  cdg_node_dealloc (TYPE_1__*) ; 

__attribute__((used)) static void cdg_dealloc(cdg_node_t ** root)
{
	cdg_node_t *current = *root;

	while (current) {
		if (current->left) {
			current = current->left;
		} else if (current->right) {
			current = current->right;
		} else {
			if (current->parent == NULL) {
				cdg_node_dealloc(current);
				*root = NULL;
				break;
			}
			if (current->parent->left == current) {
				current = current->parent;
				cdg_node_dealloc(current->left);
				current->left = NULL;
			} else if (current->parent->right == current) {
				current = current->parent;
				cdg_node_dealloc(current->right);
				current->right = NULL;
			}
		}
	}
}