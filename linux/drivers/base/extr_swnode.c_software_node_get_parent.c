#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct swnode {TYPE_1__* parent; } ;
struct fwnode_handle {int dummy; } ;
struct TYPE_2__ {struct fwnode_handle fwnode; } ;

/* Variables and functions */
 struct swnode* to_swnode (struct fwnode_handle const*) ; 

__attribute__((used)) static struct fwnode_handle *
software_node_get_parent(const struct fwnode_handle *fwnode)
{
	struct swnode *swnode = to_swnode(fwnode);

	return swnode ? (swnode->parent ? &swnode->parent->fwnode : NULL) : NULL;
}