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
struct swnode {int /*<<< orphan*/  child_ids; struct swnode* node; int /*<<< orphan*/  properties; scalar_t__ allocated; } ;
struct kobject {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct swnode*) ; 
 struct swnode* kobj_to_swnode (struct kobject*) ; 
 int /*<<< orphan*/  property_entries_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void software_node_release(struct kobject *kobj)
{
	struct swnode *swnode = kobj_to_swnode(kobj);

	if (swnode->allocated) {
		property_entries_free(swnode->node->properties);
		kfree(swnode->node);
	}
	ida_destroy(&swnode->child_ids);
	kfree(swnode);
}