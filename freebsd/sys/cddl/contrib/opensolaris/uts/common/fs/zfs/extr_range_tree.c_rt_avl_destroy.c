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
typedef  int /*<<< orphan*/  range_tree_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_numnodes (int /*<<< orphan*/ *) ; 

void
rt_avl_destroy(range_tree_t *rt, void *arg)
{
	avl_tree_t *tree = arg;

	ASSERT0(avl_numnodes(tree));
	avl_destroy(tree);
}