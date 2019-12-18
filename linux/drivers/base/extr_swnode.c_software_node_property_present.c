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
struct swnode {TYPE_1__* node; } ;
struct fwnode_handle {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  properties; } ;

/* Variables and functions */
 int /*<<< orphan*/  property_entry_get (int /*<<< orphan*/ ,char const*) ; 
 struct swnode* to_swnode (struct fwnode_handle const*) ; 

__attribute__((used)) static bool software_node_property_present(const struct fwnode_handle *fwnode,
					   const char *propname)
{
	struct swnode *swnode = to_swnode(fwnode);

	return !!property_entry_get(swnode->node->properties, propname);
}