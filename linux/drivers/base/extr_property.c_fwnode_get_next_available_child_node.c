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

/* Variables and functions */
 scalar_t__ fwnode_device_is_available (struct fwnode_handle*) ; 
 struct fwnode_handle* fwnode_get_next_child_node (struct fwnode_handle const*,struct fwnode_handle*) ; 

struct fwnode_handle *
fwnode_get_next_available_child_node(const struct fwnode_handle *fwnode,
				     struct fwnode_handle *child)
{
	struct fwnode_handle *next_child = child;

	if (!fwnode)
		return NULL;

	do {
		next_child = fwnode_get_next_child_node(fwnode, next_child);

		if (!next_child || fwnode_device_is_available(next_child))
			break;
	} while (next_child);

	return next_child;
}