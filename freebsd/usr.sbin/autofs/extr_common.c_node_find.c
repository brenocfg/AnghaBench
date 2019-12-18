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
struct node {int /*<<< orphan*/ * n_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct node* node_find_x (struct node*,char const*) ; 

struct node *
node_find(struct node *root, const char *path)
{
	struct node *node;

	assert(root->n_parent == NULL);

	node = node_find_x(root, path);
	if (node != NULL)
		assert(node != root);

	return (node);
}