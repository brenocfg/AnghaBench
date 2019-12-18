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
struct swnode {int dummy; } ;
struct software_node {struct software_node const* parent; } ;

/* Variables and functions */
 int EEXIST ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 struct swnode* software_node_to_swnode (struct software_node const*) ; 
 int /*<<< orphan*/  swnode_register (struct software_node const*,struct swnode*,int /*<<< orphan*/ ) ; 

int software_node_register(const struct software_node *node)
{
	struct swnode *parent = software_node_to_swnode(node->parent);

	if (software_node_to_swnode(node))
		return -EEXIST;

	return PTR_ERR_OR_ZERO(swnode_register(node, parent, 0));
}