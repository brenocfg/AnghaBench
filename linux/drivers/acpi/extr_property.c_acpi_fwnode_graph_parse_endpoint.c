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
typedef  struct fwnode_handle const fwnode_handle ;
struct fwnode_endpoint {int /*<<< orphan*/  id; int /*<<< orphan*/  port; struct fwnode_handle const* local_fwnode; } ;

/* Variables and functions */
 struct fwnode_handle const* fwnode_get_parent (struct fwnode_handle const*) ; 
 scalar_t__ fwnode_property_read_u32 (struct fwnode_handle const*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_fwnode_graph_parse_endpoint(const struct fwnode_handle *fwnode,
					    struct fwnode_endpoint *endpoint)
{
	struct fwnode_handle *port_fwnode = fwnode_get_parent(fwnode);

	endpoint->local_fwnode = fwnode;

	if (fwnode_property_read_u32(port_fwnode, "reg", &endpoint->port))
		fwnode_property_read_u32(port_fwnode, "port", &endpoint->port);
	if (fwnode_property_read_u32(fwnode, "reg", &endpoint->id))
		fwnode_property_read_u32(fwnode, "endpoint", &endpoint->id);

	return 0;
}