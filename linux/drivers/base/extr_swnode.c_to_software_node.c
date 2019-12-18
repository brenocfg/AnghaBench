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
struct swnode {struct software_node const* node; } ;
struct software_node {int dummy; } ;
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 struct swnode* to_swnode (struct fwnode_handle*) ; 

const struct software_node *to_software_node(struct fwnode_handle *fwnode)
{
	struct swnode *swnode = to_swnode(fwnode);

	return swnode ? swnode->node : NULL;
}