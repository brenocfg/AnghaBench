#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int portnum; int /*<<< orphan*/  ext_portnum; TYPE_2__* node; } ;
typedef  TYPE_1__ ibnd_port_t ;
struct TYPE_10__ {int ch_anafanum; int /*<<< orphan*/  ch_found; } ;
typedef  TYPE_2__ ibnd_node_t ;

/* Variables and functions */
 int /*<<< orphan*/ ** int2ext_map_sfb4700x2 ; 
 int /*<<< orphan*/ ** int2ext_map_slb2024 ; 
 int /*<<< orphan*/ ** int2ext_map_slb24 ; 
 int /*<<< orphan*/ * int2ext_map_slb4018 ; 
 int /*<<< orphan*/ ** int2ext_map_slb8 ; 
 int /*<<< orphan*/  is_line (TYPE_2__*) ; 
 scalar_t__ is_line_2024 (TYPE_2__*) ; 
 scalar_t__ is_line_24 (TYPE_2__*) ; 
 int is_line_4700 (TYPE_2__*) ; 
 int is_spine_4700x2 (TYPE_2__*) ; 

__attribute__((used)) static void voltaire_portmap(ibnd_port_t * port)
{
	int portnum = port->portnum;
	int chipnum = 0;
	ibnd_node_t *node = port->node;
	int is_4700_line = is_line_4700(node);
	int is_4700x2_spine = is_spine_4700x2(node);

	if (!node->ch_found || (!is_line(node) && !is_4700x2_spine)) {
		port->ext_portnum = 0;
		return;
	}

	if (((is_4700_line || is_4700x2_spine) &&
	     (portnum < 19 || portnum > 36)) ||
	    ((!is_4700_line && !is_4700x2_spine) &&
	     (portnum < 13 || portnum > 24))) {
			port->ext_portnum = 0;
		return;
	}

	if (port->node->ch_anafanum < 1 || port->node->ch_anafanum > 2) {
		port->ext_portnum = 0;
		return;
	}

	chipnum = port->node->ch_anafanum - 1;

	if (is_line_24(node))
		port->ext_portnum = int2ext_map_slb24[chipnum][portnum];
	else if (is_line_2024(node))
		port->ext_portnum = int2ext_map_slb2024[chipnum][portnum];
	/* sLB-4018: Only one asic per LB */
	else if (is_4700_line)
		port->ext_portnum = int2ext_map_slb4018[portnum];
	/* sFB-4700X2 4X port */
	else if (is_4700x2_spine)
		port->ext_portnum = int2ext_map_sfb4700x2[chipnum][portnum];
	else
		port->ext_portnum = int2ext_map_slb8[chipnum][portnum];
}