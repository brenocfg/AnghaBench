#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int portnum; struct TYPE_16__* remoteport; TYPE_2__* node; } ;
typedef  TYPE_1__ ibnd_port_t ;
struct TYPE_17__ {int ch_found; int numports; scalar_t__ type; TYPE_1__** ports; int /*<<< orphan*/  ch_type; } ;
typedef  TYPE_2__ ibnd_node_t ;

/* Variables and functions */
 scalar_t__ IB_NODE_SWITCH ; 
 int /*<<< orphan*/  get_router_slot (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  get_sfb_slot (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  get_slb_slot (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ is_line (TYPE_2__*) ; 
 int is_line_4700 (TYPE_2__*) ; 
 scalar_t__ is_router (TYPE_2__*) ; 
 scalar_t__ is_spine (TYPE_2__*) ; 
 int is_spine_4700x2 (TYPE_2__*) ; 
 int /*<<< orphan*/  voltaire_portmap (TYPE_1__*) ; 

__attribute__((used)) static int fill_voltaire_chassis_record(ibnd_node_t * node)
{
	int p = 0;
	ibnd_port_t *port;
	ibnd_node_t *remnode = 0;

	if (node->ch_found)	/* somehow this node has already been passed */
		return 0;
	node->ch_found = 1;

	/* node is router only in case of using unique lid */
	/* (which is lid of chassis router port) */
	/* in such case node->ports is actually a requested port... */
	if (is_router(node))
		/* find the remote node */
		for (p = 1; p <= node->numports; p++) {
			port = node->ports[p];
			if (port && is_spine(port->remoteport->node))
				get_router_slot(node, port->remoteport);
		}
	else if (is_spine(node)) {
		int is_4700x2 = is_spine_4700x2(node);

		for (p = 1; p <= node->numports; p++) {
			port = node->ports[p];
			if (!port || !port->remoteport)
				continue;

			/*
			 * Skip ISR4700 double density fabric boards ports 19-36
			 * as they are chassis external ports
			 */
			if (is_4700x2 && (port->portnum > 18))
				continue;

			remnode = port->remoteport->node;
			if (remnode->type != IB_NODE_SWITCH) {
				if (!remnode->ch_found)
					get_router_slot(remnode, port);
				continue;
			}
			if (!node->ch_type)
				/* we assume here that remoteport belongs to line */
				get_sfb_slot(node, port->remoteport);

			/* we could break here, but need to find if more routers connected */
		}

	} else if (is_line(node)) {
		int is_4700_line = is_line_4700(node);

		for (p = 1; p <= node->numports; p++) {
			port = node->ports[p];
			if (!port || !port->remoteport)
				continue;

			if ((is_4700_line && (port->portnum > 18)) ||
			    (!is_4700_line && (port->portnum > 12)))
				continue;

			/* we assume here that remoteport belongs to spine */
			get_slb_slot(node, port->remoteport);
			break;
		}
	}

	/* for each port of this node, map external ports */
	for (p = 1; p <= node->numports; p++) {
		port = node->ports[p];
		if (!port)
			continue;
		voltaire_portmap(port);
	}

	return 0;
}