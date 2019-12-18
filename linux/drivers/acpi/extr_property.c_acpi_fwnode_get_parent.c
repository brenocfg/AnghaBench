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
 struct fwnode_handle* acpi_node_get_parent (struct fwnode_handle*) ; 

__attribute__((used)) static struct fwnode_handle *
acpi_fwnode_get_parent(struct fwnode_handle *fwnode)
{
	return acpi_node_get_parent(fwnode);
}