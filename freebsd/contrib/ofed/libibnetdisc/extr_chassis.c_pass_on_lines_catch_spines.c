#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int portnum; TYPE_1__* remoteport; } ;
typedef  TYPE_2__ ibnd_port_t ;
struct TYPE_12__ {int numports; int /*<<< orphan*/  ch_found; TYPE_2__** ports; } ;
typedef  TYPE_3__ ibnd_node_t ;
struct TYPE_13__ {TYPE_3__** linenode; } ;
typedef  TYPE_4__ ibnd_chassis_t ;
struct TYPE_10__ {TYPE_3__* node; } ;

/* Variables and functions */
 int LINES_MAX_NUM ; 
 scalar_t__ insert_spine (TYPE_3__*,TYPE_4__*) ; 
 scalar_t__ is_line (TYPE_3__*) ; 
 int is_line_4700 (TYPE_3__*) ; 

__attribute__((used)) static int pass_on_lines_catch_spines(ibnd_chassis_t * chassis)
{
	ibnd_node_t *node, *remnode;
	ibnd_port_t *port;
	int i, p;

	for (i = 1; i <= LINES_MAX_NUM; i++) {
		int is_4700_line;

		node = chassis->linenode[i];

		if (!(node && is_line(node)))
			continue;	/* empty slot or router */

		is_4700_line = is_line_4700(node);

		for (p = 1; p <= node->numports; p++) {

			port = node->ports[p];
			if (!port || !port->remoteport)
				continue;

			if ((is_4700_line && (port->portnum > 18)) ||
			    (!is_4700_line && (port->portnum > 12)))
				continue;

			remnode = port->remoteport->node;

			if (!remnode->ch_found)
				continue;	/* some error - spine not initialized ? FIXME */
			if (insert_spine(remnode, chassis))
				return -1;
		}
	}
	return 0;
}