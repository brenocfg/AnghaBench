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
struct fwnode_handle {int dummy; } ;
struct swnode {struct fwnode_handle fwnode; int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_get (int /*<<< orphan*/ *) ; 
 struct swnode* to_swnode (struct fwnode_handle*) ; 

__attribute__((used)) static struct fwnode_handle *software_node_get(struct fwnode_handle *fwnode)
{
	struct swnode *swnode = to_swnode(fwnode);

	kobject_get(&swnode->kobj);

	return &swnode->fwnode;
}