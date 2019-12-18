#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct guids {scalar_t__ searchguid; scalar_t__ before; scalar_t__ after; int /*<<< orphan*/  found; int /*<<< orphan*/  searchguid_found; } ;
struct TYPE_5__ {scalar_t__ guid; } ;
typedef  TYPE_1__ ibnd_port_t ;
struct TYPE_6__ {scalar_t__ guid; scalar_t__ type; int numports; TYPE_1__** ports; } ;
typedef  TYPE_2__ ibnd_node_t ;

/* Variables and functions */
 scalar_t__ IB_NODE_SWITCH ; 
 int /*<<< orphan*/  update_switchportguids (TYPE_2__*) ; 

__attribute__((used)) static void replace_portguid(ibnd_node_t *node, void *user_data)
{
	struct guids *guids;

	guids = (struct guids *)user_data;

	if (node->guid != guids->searchguid)
		return;

	guids->searchguid_found++;

	if (node->type == IB_NODE_SWITCH) {
		/* port guids are identical to switch guids on
		 * switches, so update switch guid too
		 */
		if (node->guid == guids->before) {
			node->guid = guids->after;
			update_switchportguids(node);
			guids->found++;
		}
	}
	else {
		ibnd_port_t *port;
		int p;

		for (p = 1; p <= node->numports; p++) {
			port = node->ports[p];
			if (port
			    && port->guid == guids->before) {
				port->guid = guids->after;
				guids->found++;
				break;
			}
		}
	}
}