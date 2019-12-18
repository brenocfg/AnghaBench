#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t portnum; int /*<<< orphan*/  info; } ;
typedef  TYPE_1__ ibnd_port_t ;
struct TYPE_7__ {size_t numports; TYPE_1__** ports; int /*<<< orphan*/  guid; } ;
typedef  TYPE_2__ ibnd_node_t ;

/* Variables and functions */
 int IB_LINK_DOWN ; 
 int /*<<< orphan*/  IB_PORT_STATE_F ; 
 int /*<<< orphan*/  filterdownports_fabric ; 
 TYPE_2__* ibnd_find_node_guid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mad_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int filterdownport_check(ibnd_node_t * node, ibnd_port_t * port)
{
	ibnd_node_t *fsw;
	ibnd_port_t *fport;
	int fistate;

	fsw = ibnd_find_node_guid(filterdownports_fabric, node->guid);

	if (!fsw)
		return 0;

	if (port->portnum > fsw->numports)
		return 0;

	fport = fsw->ports[port->portnum];

	if (!fport)
		return 0;

	fistate = mad_get_field(fport->info, 0, IB_PORT_STATE_F);

	return (fistate == IB_LINK_DOWN) ? 1 : 0;
}