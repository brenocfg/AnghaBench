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
typedef  int /*<<< orphan*/  space_ref_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avl_destroy_nodes (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 

void
space_reftree_destroy(avl_tree_t *t)
{
	space_ref_t *sr;
	void *cookie = NULL;

	while ((sr = avl_destroy_nodes(t, &cookie)) != NULL)
		kmem_free(sr, sizeof (*sr));

	avl_destroy(t);
}