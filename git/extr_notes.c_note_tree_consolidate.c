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
struct int_node {void** a; } ;

/* Variables and functions */
 struct int_node* CLR_PTR_TYPE (void*) ; 
 scalar_t__ GET_PTR_TYPE (void*) ; 
 scalar_t__ PTR_TYPE_NOTE ; 
 scalar_t__ PTR_TYPE_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (struct int_node*) ; 

__attribute__((used)) static int note_tree_consolidate(struct int_node *tree,
	struct int_node *parent, unsigned char index)
{
	unsigned int i;
	void *p = NULL;

	assert(tree && parent);
	assert(CLR_PTR_TYPE(parent->a[index]) == tree);

	for (i = 0; i < 16; i++) {
		if (GET_PTR_TYPE(tree->a[i]) != PTR_TYPE_NULL) {
			if (p) /* more than one entry */
				return -2;
			p = tree->a[i];
		}
	}

	if (p && (GET_PTR_TYPE(p) != PTR_TYPE_NOTE))
		return -2;
	/* replace tree with p in parent[index] */
	parent->a[index] = p;
	free(tree);
	return 0;
}