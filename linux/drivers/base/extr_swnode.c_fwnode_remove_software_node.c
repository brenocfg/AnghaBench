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
struct swnode {int /*<<< orphan*/  kobj; int /*<<< orphan*/  id; int /*<<< orphan*/  entry; TYPE_1__* parent; } ;
struct fwnode_handle {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  child_ids; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swnode_root_ids ; 
 struct swnode* to_swnode (struct fwnode_handle*) ; 

void fwnode_remove_software_node(struct fwnode_handle *fwnode)
{
	struct swnode *swnode = to_swnode(fwnode);

	if (!swnode)
		return;

	if (swnode->parent) {
		ida_simple_remove(&swnode->parent->child_ids, swnode->id);
		list_del(&swnode->entry);
	} else {
		ida_simple_remove(&swnode_root_ids, swnode->id);
	}

	kobject_put(&swnode->kobj);
}