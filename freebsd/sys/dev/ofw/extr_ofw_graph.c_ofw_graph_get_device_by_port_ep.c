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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * OF_device_from_xref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_xref_from_node (scalar_t__) ; 
 scalar_t__ ofw_graph_get_endpoint_by_idx (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_graph_get_port_by_idx (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_graph_get_remote_endpoint (scalar_t__) ; 
 scalar_t__ ofw_graph_get_remote_parent (scalar_t__) ; 

device_t
ofw_graph_get_device_by_port_ep(phandle_t node, uint32_t port_id, uint32_t ep_id)
{
	phandle_t outport, port, endpoint, remote;

	port = ofw_graph_get_port_by_idx(node, port_id);
	if (port == 0)
		return (NULL);
	endpoint = ofw_graph_get_endpoint_by_idx(port, ep_id);
	if (endpoint == 0)
		return NULL;
	remote = ofw_graph_get_remote_endpoint(endpoint);
	if (remote == 0)
		return (NULL);
	outport = ofw_graph_get_remote_parent(remote);
	if (outport == 0)
		return (NULL);

	return (OF_device_from_xref(OF_xref_from_node(outport)));
}