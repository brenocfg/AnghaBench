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
struct node {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hugetlb_unregister_node (struct node*) ; 
 int /*<<< orphan*/  node_remove_accesses (struct node*) ; 
 int /*<<< orphan*/  node_remove_caches (struct node*) ; 

void unregister_node(struct node *node)
{
	hugetlb_unregister_node(node);		/* no-op, if memoryless node */
	node_remove_accesses(node);
	node_remove_caches(node);
	device_unregister(&node->dev);
}