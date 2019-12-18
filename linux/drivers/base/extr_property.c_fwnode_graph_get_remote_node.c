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
typedef  scalar_t__ u32 ;
struct fwnode_handle {int dummy; } ;
struct fwnode_endpoint {scalar_t__ port; scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ fwnode_device_is_available (struct fwnode_handle*) ; 
 struct fwnode_handle* fwnode_graph_get_next_endpoint (struct fwnode_handle const*,struct fwnode_handle*) ; 
 struct fwnode_handle* fwnode_graph_get_remote_port_parent (struct fwnode_handle*) ; 
 int fwnode_graph_parse_endpoint (struct fwnode_handle*,struct fwnode_endpoint*) ; 

struct fwnode_handle *
fwnode_graph_get_remote_node(const struct fwnode_handle *fwnode, u32 port_id,
			     u32 endpoint_id)
{
	struct fwnode_handle *endpoint = NULL;

	while ((endpoint = fwnode_graph_get_next_endpoint(fwnode, endpoint))) {
		struct fwnode_endpoint fwnode_ep;
		struct fwnode_handle *remote;
		int ret;

		ret = fwnode_graph_parse_endpoint(endpoint, &fwnode_ep);
		if (ret < 0)
			continue;

		if (fwnode_ep.port != port_id || fwnode_ep.id != endpoint_id)
			continue;

		remote = fwnode_graph_get_remote_port_parent(endpoint);
		if (!remote)
			return NULL;

		return fwnode_device_is_available(remote) ? remote : NULL;
	}

	return NULL;
}