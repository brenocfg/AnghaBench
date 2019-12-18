#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/ * info; int /*<<< orphan*/  base_lid; int /*<<< orphan*/  portnum; TYPE_2__* node; int /*<<< orphan*/ * ext_info; } ;
typedef  TYPE_3__ ibnd_port_t ;
typedef  int /*<<< orphan*/  ib_portid_t ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__** ports; } ;
struct TYPE_5__ {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int CL_NTOH32 (int /*<<< orphan*/ ) ; 
 int FDR10 ; 
 int /*<<< orphan*/  IBND_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IB_MLNX_EXT_PORT_LINK_SPEED_ACTIVE_F ; 
 scalar_t__ IB_NODE_SWITCH ; 
 int /*<<< orphan*/  IB_PORT_CAPMASK_F ; 
 int /*<<< orphan*/  IB_PORT_CAP_HAS_EXT_SPEEDS ; 
 int /*<<< orphan*/  IB_PORT_LINK_SPEED_ACTIVE_F ; 
 int /*<<< orphan*/  IB_PORT_LINK_SPEED_EXT_ACTIVE_F ; 
 int /*<<< orphan*/  IB_PORT_LINK_WIDTH_ACTIVE_F ; 
 int /*<<< orphan*/  IB_PORT_PHYS_STATE_F ; 
 int /*<<< orphan*/  IB_PORT_STATE_F ; 
 int /*<<< orphan*/  mad_dump_val (int /*<<< orphan*/ ,char*,int,int*) ; 
 int mad_get_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portid2str (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void debug_port(ib_portid_t * portid, ibnd_port_t * port)
{
	char width[64], speed[64];
	int iwidth;
	int ispeed, fdr10, espeed;
	uint8_t *info;
	uint32_t cap_mask;

	iwidth = mad_get_field(port->info, 0, IB_PORT_LINK_WIDTH_ACTIVE_F);
	ispeed = mad_get_field(port->info, 0, IB_PORT_LINK_SPEED_ACTIVE_F);
	fdr10 = mad_get_field(port->ext_info, 0,
			      IB_MLNX_EXT_PORT_LINK_SPEED_ACTIVE_F);

	if (port->node->type == IB_NODE_SWITCH)
		info = (uint8_t *)&port->node->ports[0]->info;
	else
		info = (uint8_t *)&port->info;
	cap_mask = mad_get_field(info, 0, IB_PORT_CAPMASK_F);
	if (cap_mask & CL_NTOH32(IB_PORT_CAP_HAS_EXT_SPEEDS))
		espeed = mad_get_field(port->info, 0, IB_PORT_LINK_SPEED_EXT_ACTIVE_F);
	else
		espeed = 0;
	IBND_DEBUG
	    ("portid %s portnum %d: base lid %d state %d physstate %d %s %s %s %s\n",
	     portid2str(portid), port->portnum, port->base_lid,
	     mad_get_field(port->info, 0, IB_PORT_STATE_F),
	     mad_get_field(port->info, 0, IB_PORT_PHYS_STATE_F),
	     mad_dump_val(IB_PORT_LINK_WIDTH_ACTIVE_F, width, 64, &iwidth),
	     mad_dump_val(IB_PORT_LINK_SPEED_ACTIVE_F, speed, 64, &ispeed),
	     (fdr10 & FDR10) ? "FDR10"  : "",
	     mad_dump_val(IB_PORT_LINK_SPEED_EXT_ACTIVE_F, speed, 64, &espeed));
}